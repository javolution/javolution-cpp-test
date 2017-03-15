/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include "java/lang/Thread.hpp"
#include "junit/framework/TestCase.hpp"
#include "junit/framework/TestSuite.hpp"
using namespace junit::framework;

namespace java {
namespace lang {

class ThreadTest: public TestCase {
public:
    static bool extendingThreadSuccess;
    static bool runnableSuccess;

    class Value: public TestCase::Value {
    public:

        void testExtendingThread() {
            extendingThreadSuccess = false;
            class MyThread : public virtual Thread {
            public:
                MyThread(Value* value) : Object(value) {}
                class Value : public Thread::Value {
                    void run() override {
                        extendingThreadSuccess = true;
                    }
                };
            };
            MyThread thread = new MyThread::Value();
            thread.start();
            Thread::sleep(1000);
            assertTrue(extendingThreadSuccess);
        }

        void testRunnableThread() {
            runnableSuccess = false;
            class MyRunnable : public virtual Runnable {
            public:
                MyRunnable(Value* value) : Object(value) {}
                class Value : public Object::Value, public virtual Runnable::Interface {
                    void run() override {
                        runnableSuccess = true;
                    }
                };
            };
            MyRunnable myRunnable = new MyRunnable::Value();
            Thread thread = new Thread::Value(myRunnable);
            thread.start();
            Thread::sleep(1000);
            assertTrue(runnableSuccess);
        }
    };

    CTOR (ThreadTest, Value)
    TEST (testExtendingThread)
    TEST (testRunnableThread)

    static TestSuite suite() {
        TestSuite tests = new TestSuite::Value();
        tests.addTest(new testExtendingThread());
        tests.addTest(new testRunnableThread());
        return tests;
    }
};

}
}

bool java::lang::ThreadTest::extendingThreadSuccess = false;
bool java::lang::ThreadTest::runnableSuccess = false;
