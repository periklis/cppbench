// -*-c++-*-

#ifndef INIT_PROCEDURES_H_
#define INIT_PROCEDURES_H_

namespace cppbench {

  class UndefinedDefaultInitClass {
  public:
    UndefinedDefaultInitClass() = default;
    int getAnIntMember() { return this->anIntMember; }
    char getACharMember() { return this->aCharMember; }
    float getAFloatMember() { return this->aFloatMember; }
  private:
    int anIntMember;
    char aCharMember;
    float aFloatMember;
  };

  class ValueDefaultInitClass {
  public:
    ValueDefaultInitClass() = default;
    int getAnIntMember() { return this->anIntMember; }
    char getACharMember() { return this->aCharMember; }
    float getAFloatMember() { return this->aFloatMember; }
  private:
    int anIntMember {};
    char aCharMember {};
    float aFloatMember {};
  };

  class DefaultInitClass {
  public:
    DefaultInitClass()
      : anIntMember(0), aCharMember('\0'), aFloatMember(0.0) {}

    int getAnIntMember() { return this->anIntMember; }
    char getACharMember() { return this->aCharMember; }
    float getAFloatMember() { return this->aFloatMember; }
  private:
    int anIntMember;
    char aCharMember;
    float aFloatMember;
  };

  class CopyInitClass {
  public:
    explicit CopyInitClass (int i) : anIntMember(i) {}
    CopyInitClass (const CopyInitClass& other)
      : anIntMember(other.anIntMember) {}

    int getAnIntMember() { return this->anIntMember; }
  private:
    int anIntMember;
  };
}
#endif
