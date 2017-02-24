#ifndef VECTOR_H_
#define VECTOR_H_

#include <algorithm>
#include <iterator>

/*
 * TODO: Refactor constructor duplicate code
 * TODO: Add constructor for std::initializer_list<T>
 * TODO: Implement insert, emplace, erase
 * TODO: Evaluate and refactor typed testes vs. param tests
 */
namespace cppbench {
namespace containers {

template<typename T>
class vector {

 public:
  typedef T                                     value_type;
  typedef T&                                    reference;
  typedef const T&                              const_reference;
  typedef int                                   size_type;
  typedef T*                                    iterator;
  typedef const T*                              const_iterator;
  typedef std::reverse_iterator<iterator>       reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef iterator                              pointer;
  typedef const_iterator                        const_pointer;

  vector() {}

  explicit vector(size_type n)
      : buf_{n > 0 ? new value_type[2*n] : nullptr},
        begin_{buf_},
        end_{buf_ + n},
        cap_{buf_ + 2*n}
  {
    std::fill(begin_, end_, value_type{});
  }

  vector(size_type n, value_type& v)
      : buf_{n > 0 ? new value_type[2*n] : nullptr},
        begin_{buf_},
        end_{buf_ + n},
        cap_{buf_ + 2*n}
  {
    std::fill(begin_, end_, v);
  }

  vector(iterator begin, iterator end)
      : buf_{(end-begin) > 0 ? new value_type[2*(end-begin)] : nullptr},
        begin_{buf_},
        end_{buf_ + (end-begin)},
        cap_{buf_ + 2*(end-begin)}
  {
    std::copy(begin, end, begin_);
  }

  vector(const vector& v)
      : buf_{v.size() > 0 ? new value_type[2*v.size()] : nullptr},
        begin_{buf_},
        end_{buf_ + v.size()},
        cap_{buf_ + 2*v.size()}
  {
    std::copy(v.begin_, v.end_, begin_);
  }

  vector(vector&& v)
      : vector()
  {
    swap(*this, v);
  }

  ~vector()
  {
    if (buf_ != nullptr){
      delete[] buf_;
      buf_ = begin_ = end_ = cap_ = nullptr;
    }
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

  iterator begin() { return begin_; }
  const_iterator cbegin() const { return begin_;}
  iterator end() { return end_; }
  const_iterator cend() const { return end_; }

  reverse_iterator rbegin() { return reverse_iterator(end_); }
  const_reverse_iterator crbegin() const { return reverse_iterator(end_);}
  reverse_iterator rend() { return reverse_iterator(begin_); }
  const_reverse_iterator crend() const { return reverse_iterator(begin_); }

  size_type size() const { return static_cast<size_type>(end_ - begin_); }
  size_type max_size() const { return std::numeric_limits<size_type>::max(); };
  size_type capacity() const { return static_cast<size_type>(cap_ - begin_);}
  bool empty() const { return begin_ == end_; }

  void reserve(size_type n)
  {
    if (n > this->max_size() || n <= 0)
      throw std::length_error("New capacity exceeds max size!");

    if (n > this->capacity()){
      vector tmp(n/2);
      std::copy(begin_, end_, tmp.begin_);
      swap(*this, tmp);
    }
  }

  void shrink_to_fit()
  {
    size_type n = this->size();

    if(cap_ != end_) {
      auto nbuf = std::make_unique<value_type[]>(n);
      std::copy(begin_, end_, &nbuf[0]);

      auto tmp = buf_;
      buf_ = nbuf.release();
      nbuf.reset(tmp);

      begin_ = &buf_[0];
      end_ = cap_ = &buf_[n];
    }
  }

  reference operator[](size_type n) { return buf_[n]; }
  const_reference operator[](size_type n) const { return buf_[n]; }

  reference at(size_type pos)
  {
    if(!(pos < this->size()))
      throw std::out_of_range("Position out of range");

    return (*this)[pos];
  }

  const_reference at(size_type pos) const { return at(pos); }

  reference front() { return *begin_; }
  const_reference front() const { return *begin_; }
  reference back() { return *(end_ -1); }
  const_reference back() const { return *(end_ - 1); }

  void push_back(const value_type& v) { this->_push_back(v); }

  void push_back(value_type&& v) { this->_push_back(v); }

  void pop_back() {
    (--end_)->~T();
  }

  void clear() {
    while(begin_ != end_)
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
  pointer buf_ {nullptr};
  pointer begin_ {nullptr};
  pointer end_ {nullptr};
  pointer cap_ {nullptr};

  template<typename ValueT>
  void _push_back(ValueT&& v)
  {
    if (end_ != cap_) {
      *end_ = v;
      ++end_;
    } else {
      vector tmp {begin_, end_};
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
