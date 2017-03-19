/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include "junit/framework/TestCase.hpp"
#include "junit/framework/TestSuite.hpp"
#include "java/lang/System.hpp"
#include "java/lang/Double.hpp"

using namespace junit::framework;

namespace java {
namespace lang {

class ObjectTest: public TestCase {
public:
    class Value: public TestCase::Value {
    public:
        static const int COUNT = 10000000;
        static const int USAGE = 1000000;

        void testStandardHeap() {
            static Object vector[USAGE];
            Type::int64 start = System::currentTimeMillis();
            for (int i = 0; i < COUNT; i++) {
                vector[i % USAGE] = new Object::Value();
            }
            Type::int64 end = System::currentTimeMillis();
            System::out.println(
                    "Number of objects allocated and destroyed per second: "
                            + String::valueOf(COUNT * 1000.0 / (end - start)));
        }

        void testFastHeap() {
            static Object vector[USAGE];
            FastHeap::setSize(1024 * 1024); // Blocks.
            FastHeap::enable();
            Type::int64 start = System::currentTimeMillis();
            for (int i = 0; i < COUNT; i++) {
                vector[i % USAGE] = new Object::Value();
            }
            Type::int64 end = System::currentTimeMillis();
            System::out.println(
                    "Number of objects allocated and destroyed per second: "
                            + String::valueOf(COUNT * 1000.0 / (end - start)));
            FastHeap::disable();
            Type::int64 systemHeapCount = FastHeap::getSystemHeapCount();
            assertTrue("Number of system heap allocations should be zero but was: " +
                    String::valueOf(systemHeapCount), systemHeapCount == 0);
        }

        void testStack() {
            static Double vector[USAGE]; // Double is a Value-Type.
            Type::int64 start = System::currentTimeMillis();
            for (int i = 0; i < COUNT; i++) {
                vector[i % USAGE] = 1.23;
            }
            Type::int64 end = System::currentTimeMillis();
            System::out.println(
                    "Number of objects allocated and destroyed per second: "
                            + String::valueOf(COUNT * 1000.0 / (end - start)));
        }

    };

    CLASS_BASE (ObjectTest, TestCase)
    TEST (testStandardHeap)
    TEST (testFastHeap)
    TEST (testStack)

    static TestSuite suite() {
        TestSuite tests = new TestSuite::Value();
        tests.addTest(new testStandardHeap());
        tests.addTest(new testFastHeap());
        tests.addTest(new testStack());
        return tests;
    }
};

}
}
