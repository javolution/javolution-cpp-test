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
        static bool isNullByValue(Object obj) {
            return obj == nullptr;
        }
        static bool isNullByConstRef(const Object& obj) {
            return obj == nullptr;
        }

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
            assertTrue("Number of system heap allocations should be zero but was: " + String::valueOf(systemHeapCount),
                    systemHeapCount == 0);
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

        void testValuePassing() {
            static Object vector[USAGE];
            for (int i = 0; i < USAGE; i++) {
                vector[i] = new Object::Value();
            }

            Type::int64 start = System::currentTimeMillis();
            for (int i = 0; i < COUNT; i++)
                if (vector[i % USAGE] == nullptr)
                    fail();
            Type::int64 end = System::currentTimeMillis();
            Type::int64 offset = end - start;

            start = System::currentTimeMillis();
            for (int i = 0; i < COUNT; i++)
                if (isNullByValue(vector[i % USAGE]))
                    fail();
            end = System::currentTimeMillis();
            Type::int64 time = end - start - offset;

            System::out.println("Cost of passing smart pointers by value: "
                    + String::valueOf(time * 1000.0 / COUNT) + u" μs");
        }

        void testConstRefPassing() {
              static Object vector[USAGE];
              for (int i = 0; i < USAGE; i++) {
                  vector[i] = new Object::Value();
              }

              Type::int64 start = System::currentTimeMillis();
              for (int i = 0; i < COUNT; i++)
                  if (vector[i % USAGE] == nullptr)
                      fail();
              Type::int64 end = System::currentTimeMillis();
              Type::int64 offset = end - start;

              start = System::currentTimeMillis();
              for (int i = 0; i < COUNT; i++)
                  if (isNullByConstRef(vector[i % USAGE]))
                      fail();
              end = System::currentTimeMillis();
              Type::int64 time = end - start - offset;

              System::out.println("Cost of passing smart pointers by const reference (const&): "
                      + String::valueOf(time * 1000.0 / COUNT) + u" μs");
          }
    };

    CLASS_BASE (ObjectTest, TestCase)
    TEST (testStandardHeap)
    TEST (testFastHeap)
    TEST (testStack)
    TEST (testValuePassing)
    TEST (testConstRefPassing)

    static TestSuite suite() {
        TestSuite tests = new TestSuite::Value();
        tests.addTest(new testStandardHeap());
        tests.addTest(new testFastHeap());
        tests.addTest(new testStack());
        tests.addTest(new testValuePassing());
        tests.addTest(new testConstRefPassing());
        return tests;
    }
};

}}
