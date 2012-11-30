
#ifndef HTEST_HTEST_H_
#define HTEST_HTEST_H_

#include <exception>
#include <list>

namespace htest {
  class Test {
    public:
    virtual void TestBody() = 0;

    bool Run () {
      try {
        TestBody();
      } catch (std::exception const&) {
        return false;
      }
      return true;
    }

    void Assert (bool a_value) {
      if (a_value == false) {
        throw std::exception();
      }
    }
  };

  class TestBucket {
    public:
    static int Register (Test* a_test) {
      if (!instance) {
        instance = new TestBucket();
      }

      instance->tests_.push_back(a_test);
      return 0;
    }

    std::list<Test*> tests_;

    static TestBucket* instance;
    static const std::list<Test*> tests () { return instance->tests_; }
  };
}

#define HTEST_TEST_CLASS_NAME_(test_case_name, test_name) test_case_name##_##test_name##_Test

#define HTEST(test_case_name, test_name, description)\
class HTEST_TEST_CLASS_NAME_(test_case_name, test_name) : public htest::Test {\
  public:\
  HTEST_TEST_CLASS_NAME_(test_case_name, test_name)() {}\
  \
  private:\
  virtual void TestBody();\
  const char* Description () { return description; }\
  static int const test_info_;\
};\
\
int const HTEST_TEST_CLASS_NAME_(test_case_name, test_name)\
  ::test_info_ =\
    ::htest::TestBucket::Register(\
      new HTEST_TEST_CLASS_NAME_(test_case_name, test_name)());\
void HTEST_TEST_CLASS_NAME_(test_case_name, test_name)::TestBody()

#endif

