#ifndef _COMPARABLE_H
#define _COMPARABLE_H

template <class T = int>
class Comparable{
protected:
  T& value;
public:
  Comparable(T& v):value(v){}
  Comparable<T>& operator=(const Comparable<T>& c);
  bool operator<(Comparable<T>& c);
  bool operator<=(Comparable<T>& c);
  bool operator>(Comparable<T>& c);
  bool operator>=(Comparable<T>& c);
};

template <class T>
bool Comparable<T>::operator<(Comparable<T>& c){
  return value < c.value;
}
template <class T>
bool Comparable<T>::operator<=(Comparable<T>& c){
  return value <= c.value;
}
template <class T>
bool Comparable<T>::operator>(Comparable<T>& c){
  return value > c.value;
}
template <class T>
bool Comparable<T>::operator>=(Comparable<T>& c){
  return value >= c.value;
}

template <class T>
struct sComparable{
  T& value;

  sComparable(T& v):value(v){}

  //sComparable(const sComparable& s):value(s.value){}

  sComparable<T>& operator=(const sComparable& s){
    value = s.value;
    return *this;
  }

  bool operator<(sComparable<T>& c){
    return value < c.value;
  }

  bool operator<=(sComparable<T>& c){
    return value <= c.value;
  }

  bool operator>(sComparable<T>& c){
    return value > c.value;
  }

  bool operator>=(sComparable<T>& c){
    return value >= c.value;
  }

};

#endif
