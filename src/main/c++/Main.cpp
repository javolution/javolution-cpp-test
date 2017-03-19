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
    class TestProgress: public TestListener {
    public:
        class Value: public Object::Value, public virtual TestListener::Interface {
            void addError(const Test&, const Throwable& e) override {
                System::out.println("  --  Unexpected Error -- " + e.toString());
                System::out.println(e.getStackTrace());
            }
            void addFailure(const Test&, const AssertionFailedError& e) override {
                System::out.println("   --  Assertion Failed -- " + e.toString());
            }
            void endTest(const Test&) override {
            }
            void startTest(const Test& test) override {
                TestCase testCase = test.cast_<TestCase::Value>();
                System::out.println(testCase.getName());
            }
        };
        TestProgress(Void = nullptr) {}
        TestProgress(Value* value) : TestListener(value)  {}
        //CTOR(TestProgress, Value)
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
    System::out.println("Number of test cases run: " + String::valueOf(result.runCount()));
    System::out.println("Number of error(s) : " + String::valueOf(result.errorCount()));
    System::out.println("Number of failure(s) : " + String::valueOf(result.failureCount()));
    if (result.wasSuccessful()) {
        System::out.println("SUCCESS !");
        return 0;
    } else {
        System::out.println("FAILURE !");
        return -1;
    }
}
