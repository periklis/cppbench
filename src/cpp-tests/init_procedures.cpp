#include <iostream>
#include <string>

#include "init_procedures.hpp"

using namespace cppbench;

/*
  Ordered static zero/empty initialization
*/
int zi;
float zf;
std::string zs;
int zari[3];

void make_zero_initialization_examples()
{
  std::cout << "In single translation unit non-local 'int zsi' has zero initialization: "
            << zi
            << std::endl;

  std::cout << "In single translation unit non-local "
            << "'float zsf' has zero initialization: "
            << zf
            << std::endl;

  std::cout << "In single translation unit non-local "
            << "'std::string zi' has zero initialization: "
            << zi
            << std::endl;

  std::cout << "In single translation unit non-local "
            << "'int zari[3] has three zero intialized members: "
            << zari[0]
            << zari[1]
            << zari[2]
            << std::endl;
}

/*
  Static constant initialization
*/
static int si;
static float sf;
static std::string ss;
static int sari[3];

void make_static_initialization_examples()
{
  std::cout << "In single translation unit non-local "
            << "'static int zsi' has zero initialization: "
            << si
            << std::endl;

  std::cout << "In single translation unit non-local "
            << "'static float zsf' has zero initialization: "
            << sf
            << std::endl;

  std::cout << "In single translation unit non-local "
            << "'static std::string zi' has zero initialization: "
            << ss
            << std::endl;

  std::cout << "In single translation unit non-local "
            << "'static int zari[3] has three zero intialized members: "
            << sari[0]
            << sari[1]
            << sari[2]
            << std::endl;
}

void make_default_initialisation_examples()
{
  int* i = new int;
  std::cout << "'int* i = new int;' has undeterminate value: "
            << *i
            << std::endl;

  std::string sar[2];

  std::cout << "\'std::string sar[2];\' has two default initialized object with"
            << " first value"
            << sar[0]
            << " second value"
            << sar[1]
            << std::endl;

  DefaultInitClass a;
  std::cout << "\'DefaultInitClass a;\' has values: "
            << a.getAnIntMember() << " "
            << a.getACharMember() << " "
            << a.getAFloatMember()
            << std::endl;

  DefaultInitClass* b = new DefaultInitClass;
  std::cout << "\'DefaultInitClass* b = new DefaultInitClass;\' has values: "
            << b->getAnIntMember() << " "
            << b->getACharMember() << " "
            << b->getAFloatMember()
            << std::endl;

  DefaultInitClass* c = new DefaultInitClass();
  std::cout << "\'DefaultInitClass* c = new DefaultInitClass();\' has values: "
            << c->getAnIntMember() << " "
            << c->getACharMember() << " "
            << c->getAFloatMember()
            << std::endl;

  delete i;
  delete b;
  delete c;
}

void make_default_initializable_object_with_undefined_members()
{
  UndefinedDefaultInitClass a;
  std::cout << "Undefined Default initializable class with an int member: "
            << a.getAnIntMember()
            << ",  with an char member: "
            << a.getACharMember()
            << " and with an float member: "
            << a.getAFloatMember()
            << std::endl;
}

void make_value_default_initialisable_object()
{
  int sa {};
  int sb ();

  std::cout << "Value initialization of scalar type "
            << "'int sa {};' defaults to zero value: "
            << sa
            << std::endl
            << "'int sb (); default to zerto value too: "
            << sb
            <<std::endl;

  // int* pva = new int();
  // std::cout << "Value initialization of scalar type on dynamic storage "
  //           << "int* pva = new int();' has zero value: "
  //           << *pva
  //           << std::endl;

  ValueDefaultInitClass a;

  std::cout << "Value default initializable class with an int member: "
            << a.getAnIntMember()
            << ",  with an char member: "
            << a.getACharMember()
            << " and with an float member: "
            << a.getAFloatMember()
            << std::endl;

  // delete pva;
}

void make_default_initialisable_object()
{
  DefaultInitClass a;

  std::cout << "Default initializable class with an int member: "
            << a.getAnIntMember()
            << ",  with an char member: "
            << a.getACharMember()
            << " and  with an float member: "
            << a.getAFloatMember()
            << std::endl;
}

void make_copy_constructed_object()
{
  CopyInitClass a {1};
  CopyInitClass b {a};

  std::cout << "Origin object with int member: "
            << a.getAnIntMember()
            << " "
            << "Copy object with int member initialised by origin: "
            << b.getAnIntMember()
            << std::endl;

  CopyInitClass c {CopyInitClass{2}};

  std::cout << "Origin temporary object with int member: 2 "
            << "Copy object with int member initialised by origin: "
            << c.getAnIntMember()
            << std::endl;
}

int main()
{
  std::cout << "---- BEGIN CASE: \"init procedures\" ----" << std::endl;
  std::cout << "---- BEGIN SUBCASE: Default Initialization ----" << std::endl;
  make_zero_initialization_examples();
  make_static_initialization_examples();
  make_default_initialisation_examples();
  make_default_initializable_object_with_undefined_members();
  std::cout << "---- END SUBCASE: Default Initialization ----" << std::endl;

  std::cout << "---- BEGIN SUBCASE: Value Initialization ----" << std::endl;
  make_value_default_initialisable_object();
  std::cout << "---- END SUBCASE: Value Initialization ----" << std::endl;

  std::cout << "---- BEGIN SUBCASE: Direct Initialization ----" << std::endl;
  make_default_initialisable_object();
  std::cout << "---- END SUBCASE: Direct Initialization ----" << std::endl;

  std::cout << "---- BEGIN SUBCASE: Copy Initialization ----" << std::endl;
  make_copy_constructed_object();
  std::cout << "---- END SUBCASE: Copy Initialization ----" << std::endl;

  std::cout << "---- END CASE: \"init procedures\" ----" << std::endl;
}
