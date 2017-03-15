/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */

#include "junit/framework/TestResult.hpp"
#include "junit/framework/TestListener.hpp"
#include "java/lang/System.hpp"
#include "java/lang/ObjectTest.hpp"
#include "java/lang/StringTest.hpp"
#include "java/lang/ThreadTest.hpp"
using namespace junit::framework;

/** Unit test main routine (with MSVC make sure that your project is of type Console Application). */
int main(int, char**) {

    // Displays test results as they go.
    class TestProgress: public virtual TestListener {
    public:
        class Value: public Object::Value, public virtual TestListener::Interface {
            void addError(const Test&, const Throwable& e) override {
                System::out.println(String::valueOf("  --  Unexpected Error -- ") + e);
                System::out.println(e.getStackTrace());
            }
            void addFailure(const Test&, const AssertionFailedError& e) override {
                System::out.println(String::valueOf("   --  Assertion Failed -- ") + e);
            }
            void endTest(const Test&) override {
            }
            void startTest(const Test& test) override {
                TestCase testCase = test.cast_<TestCase::Value>();
                System::out.println(testCase.getName());
            }
        };

        CTOR(TestProgress, Value)
    };

    TestResult result = new TestResult::Value();
    result.addListener(new TestProgress::Value());

    ////////////////////////////////////////////////////
    // Tests to run (TestSuite).
    TestSuite tests = new TestSuite::Value();
    tests.addTest(java::lang::ObjectTest::suite());
    tests.addTest(java::lang::StringTest::suite());
    tests.addTest(java::lang::ThreadTest::suite());
    ////////////////////////////////////////////////////

    System::out.println(" -- JAVOLUTION C++ TESTING --");
    tests.run(result);
    System::out.println(String::valueOf("Number of test cases run: ") + result.runCount());
    System::out.println(String::valueOf("Number of error(s) : ") + result.errorCount());
    System::out.println(String::valueOf("Number of failure(s) : ") + result.failureCount());
    if (result.wasSuccessful()) {
        System::out.println("SUCCESS !");
        return 0;
    } else {
        System::out.println("FAILURE !");
        return -1;
    }
}
