#ifndef VECTOR_H_
#define VECTOR_H_

#include <algorithm>
#include <initializer_list>
#include <iterator>

/*
 * TODO: Separate allocation policy between stack and free store through extra type parameter
 * TODO: Implement insert, emplace, erase
 */
namespace cppbench {
namespace containers {

template<typename T>
class vector_base  {
 public:
  typedef T              value_type;
  typedef int            size_type;
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

  vector(vector&& v)
      : vector()
  {
    swap(*this, v);
  }

  vector& operator=(vector v)
  {
    swap(*this, v);

    return *this;
  }

  vector& operator=(vector&& v)
  {
    vector tmp(v);
    swap(*this, tmp);

    return *this;
  }

  iterator begin() { return this->begin_; }
  const_iterator cbegin() const { return this->begin_;}
  iterator end() { return this->end_; }
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

} // namespace containers
} // namespace cppbench


#endif  // VECTOR_H_
