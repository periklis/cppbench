#ifndef VECTOR_H_
#define VECTOR_H_

#include <algorithm>
#include <initializer_list>
#include <iterator>

/*
 * TODO: Review iterator invalidation requirements.
 * TODO: Add SFINAE for constructor overloads
 * TODO: Implement emplace, erase
 */
namespace cppbench {
namespace containers {

/*
  Rationale and design of a C++11 concept-conforming vector container

  I. Requirements

  Implement a vector following closely the STL std::vector<T> API (See
  http://en.cppreference.com/w/cpp/container/vector) without
  allocators and specialization for bool type.

  This results into following requirements:
  - C++11 minimum required for API and implementation

  - Contiguous storage of a dynamic sized array of data of type T

  - Random access operations O(1)

  - Insertion/Removal at the end in amortized constant O(1)

  - Insertion/removal of elements linear in distance to the end of the
    vector O(n)

  - Container meets concepts: Container, SequenceContainer ,
    ContiguousContainer and ReversibleContainer.

  - Type T of vector element meets concepts: CopyAssignable,
    CopyConstructible, Erasable (Ops may impose stricter requirements)


  II. Design decisions

  - No usage of size_t or any unsigned built-in type for size-type to
    mitigate bugs using our API with signed built-in types.

  - Template parameter independent code is extracted into a derived
    class to minimize code size.

  - Provide public typedefs according to container concepts types (See
    http://en.cppreference.com/w/cpp/concept/Container)

  - Provide sequence container operations for construction,
    emplacement, insertion, erasure, assignment, subscript access and
    bound-checked access. (See
    http://en.cppreference.com/w/cpp/concept/SequenceContainer)

  - Provide size and capacity management and inquiry.

  - Provide strong exception safety guarantee for copy, assignment,
    move and insertion.

  - Provide efficient non-throwing swap fiend member function for ADL.

  - Provide iterators and their reverse counterparts with following
    invalidation guarantees:
    a. Insertion: No inv. before insertion point, except on capacity excess.
    b. Erasure: All iterators are invalidated after the point of erasure.
    c. Resize: Same as Insert/erase.
    d. Swap: No invalidation of any references or iterators.

  - Protection for constructor overloading for non-built-in type
    arguments. (e.g. construction by input iterator pair)

  III. Differences to STL std::vector<T>

  - No usage of allocators, direct dynamic array management on free store.

  - No debugging facility for iterators and invariants.

  - No ASAN support.

 */
template<typename T>
class vector_base  {
 public:
  typedef T              value_type;
  typedef int            size_type;
  typedef int            difference_type;
  typedef T&             reference;
  typedef const T&       const_reference;
  typedef T*             iterator;
  typedef const T*       const_iterator;
  typedef iterator       pointer;
  typedef const_iterator const_pointer;

  vector_base() {}

  explicit vector_base(size_type n)
      : buf_{n > 0 ? new value_type[2*n] : nullptr},
        begin_{buf_},
        end_{buf_ + n},
        cap_{buf_ + 2*n}
  {}

  template<typename ValueT>
  vector_base(size_type n, ValueT&& v)
      : vector_base(n)
  {
    std::fill(begin_, end_, v);
  }

  virtual ~vector_base()
  {
    if (buf_ != nullptr){
      delete[] buf_;
      buf_ = begin_ = end_ = cap_ = nullptr;
    }
  }

 protected:
  pointer buf_ {nullptr};
  pointer begin_ {nullptr};
  pointer end_ {nullptr};
  pointer cap_ {nullptr};
};


template<typename T>
class vector
    : private vector_base<T> {

 private:
  typedef vector_base<T> vector_base;

 public:
  typedef typename vector_base::value_type      value_type;
  typedef typename vector_base::reference       reference;
  typedef typename vector_base::const_reference const_reference;
  typedef typename vector_base::size_type       size_type;
  typedef typename vector_base::difference_type difference_type;
  typedef typename vector_base::iterator        iterator;
  typedef typename vector_base::const_iterator  const_iterator;
  typedef std::reverse_iterator<iterator>       reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef typename vector_base::pointer         pointer;
  typedef typename vector_base::const_pointer   const_pointer;

  vector() {}

  explicit vector(size_type n)
      : vector_base(n, value_type{}) {}

  vector(size_type n, value_type& v)
      : vector_base(n, v) {}

  vector(iterator begin, iterator end)
      : vector_base(std::distance(begin, end))
  {
    std::copy(begin, end, this->begin_);
  }

  vector(std::initializer_list<T> l)
      : vector(const_cast<iterator>(l.begin()), const_cast<iterator>(l.end())) {}

  vector(const vector& v)
      : vector_base(v.size())
  {
    std::copy(v.begin_, v.end_, this->begin_);
  }

  vector(vector&& v) noexcept
      : vector()
  {
    swap(*this, v);
  }

  vector& operator=(vector v)
  {
    if (this != v)
      swap(*this, v);

    return *this;
  }

  vector& operator=(vector&& v) noexcept
  {
    vector tmp(v);
    swap(*this, tmp);

    return *this;
  }

  iterator begin() { return this->begin_; }
  const_iterator begin() const { return this->begin_; }
  const_iterator cbegin() const { return this->begin_;}
  iterator end() { return this->end_; }
  const_iterator end() const { return this->end_; }
  const_iterator cend() const { return this->end_; }

  reverse_iterator rbegin() { return reverse_iterator(this->end_); }
  const_reverse_iterator crbegin() const { return reverse_iterator(this->end_);}
  reverse_iterator rend() { return reverse_iterator(this->begin_); }
  const_reverse_iterator crend() const { return reverse_iterator(this->begin_); }

  size_type size() const { return static_cast<size_type>(this->end_ - this->begin_); }
  size_type max_size() const { return std::numeric_limits<size_type>::max(); };
  size_type capacity() const { return static_cast<size_type>(this->cap_ - this->begin_);}
  bool empty() const { return this->begin_ == this->end_; }

  void reserve(size_type n)
  {
    if (n > this->max_size() || n <= 0)
      throw std::length_error("New capacity exceeds max size!");

    if (n > this->capacity()){
      vector tmp(n/2);
      std::copy(this->begin_, this->end_, tmp.begin_);
      swap(*this, tmp);
    }
  }

  void shrink_to_fit()
  {
    size_type n = this->size();

    if(this->cap_ != this->end_) {
      auto nbuf = std::make_unique<value_type[]>(n);
      std::copy(this->begin_, this->end_, &nbuf[0]);

      auto tmp = this->buf_;
      this->buf_ = nbuf.release();
      nbuf.reset(tmp);

      this->begin_ = &this->buf_[0];
      this->end_ = this->cap_ = &this->buf_[n];
    }
  }

  reference operator[](size_type n) { return this->buf_[n]; }
  const_reference operator[](size_type n) const { return this->buf_[n]; }

  reference at(size_type pos)
  {
    if(!(pos < this->size()))
      throw std::out_of_range("Position out of range");

    return (*this)[pos];
  }

  const_reference at(size_type pos) const { return at(pos); }

  reference front() { return *this->begin_; }
  const_reference front() const { return *this->begin_; }
  reference back() { return *(this->end_ -1); }
  const_reference back() const { return *(this->end_ - 1); }

  void push_back(const value_type& v) { this->_push_back(v); }

  void push_back(value_type&& v) { this->_push_back(v); }

  void pop_back() {
    (--this->end_)->~T();
  }

  iterator insert(size_type pos, const value_type& v)
  {
    return this->insert(pos, 1, v);
  }

  iterator insert(size_type pos, value_type&& v)
  {
    return this->insert(pos, 1, v);
  }

  iterator insert(size_type pos, size_type n, const value_type& v)
  {
    if (!(pos < this->size()))
      throw std::out_of_range("Position out of range");

    auto new_size = this->size() + n;
    if (new_size >= this->capacity()) {
      this->resize(new_size);
    }

    auto insert_pos = this->begin_ + pos;
    vector past_pos_elems {insert_pos, this->end_};

    for(size_type i = 0; i < n; ++i)
      *(insert_pos + i) = value_type{v};

    std::copy(past_pos_elems.begin_, past_pos_elems.end_,
              (insert_pos + n));

    this->end_ = this->begin_ + new_size;

    return this->begin_ + pos;
  }

  iterator insert(size_type pos, const_iterator b, const_iterator e)
  {
    if (!(pos < this->size()))
      throw std::out_of_range("Position out of range!");

    if(b > e)
      throw std::range_error("Not valid input range!");

    auto distance = std::distance(b, e);
    auto new_size = this->size() + distance;
    if (new_size >= this->capacity()) {
      this->resize(new_size);
    }

    auto insert_pos = this->begin_ + pos;
    vector past_pos_elems {insert_pos, this->end_};

    for(auto i = 0; i < distance; ++i)
      *(insert_pos + i) = *(b + i);

    std::copy(past_pos_elems.begin(), past_pos_elems.end(),
              (insert_pos + distance));

    this->end_ = this->begin_ + new_size;

    return this->begin_ + pos;
  }

  iterator insert(size_type pos, std::initializer_list<T> il)
  {
    return this->insert(pos, il.begin(), il.end());
  }

  void resize(size_type count)
  {
    if (count > this->size()) {
      vector tmp(count);
      std::copy(this->begin_, this->end_, tmp.begin_);
      swap(*this, tmp);
    } else if(count < this->size()) {
      vector tmp(count);
      std::copy(this->begin_, this->begin_ + count, tmp.begin_);
      swap(*this, tmp);
    }
  }

  void clear() {
    while(this->begin_ != this->end_)
      this->pop_back();
  }

  friend void swap(vector& first, vector& second)
  {
    using std::swap;
    swap(first.buf_, second.buf_);
    swap(first.begin_, second.begin_);
    swap(first.end_, second.end_);
    swap(first.cap_, second.cap_);
  }

 private:
  template<typename ValueT>
  void _push_back(ValueT&& v)
  {
    if (this->end_ != this->cap_) {
      *this->end_ = v;
      ++this->end_;
    } else {
      vector tmp {this->begin_, this->end_};
      *tmp.end_ = v;
      ++tmp.end_;

      swap(*this, tmp);
    }
  }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T>& v) {
  std::copy(v.cbegin(), v.cend(), std::ostream_iterator<T>(os, ", "));
  return os;
}

template<typename T>
inline bool operator==(const vector<T>& lhs, const vector<T>& rhs)
{
  return lhs.size() == rhs.size() &&
      std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<typename T>
inline bool operator!=(const vector<T>& lhs, const vector<T>& rhs)
{
  return !(lhs == rhs);
}

template<typename T>
inline bool operator<(const vector<T>& lhs, const vector<T>& rhs)
{
  return std::lexicographical_compare(
      lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<typename T>
inline bool operator<=(const vector<T>& lhs, const vector<T>& rhs)
{
  return !(rhs < lhs);
}

template<typename T>
inline bool operator>(const vector<T>& lhs, const vector<T>& rhs)
{
  return rhs < lhs;
}

template<typename T>
inline bool operator>=(const vector<T>& lhs, const vector<T>& rhs)
{
  return !(lhs < rhs);
}

} // namespace containers
} // namespace cppbench


#endif  // VECTOR_H_
