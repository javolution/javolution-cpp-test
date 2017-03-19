/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include "junit/framework/TestCase.hpp"
#include "junit/framework/TestSuite.hpp"
using namespace junit::framework;

namespace java {
namespace lang {

class StringTest: public TestCase {
public:
    class Value: public TestCase::Value {
    public:

        void testValueOf_uchar() {
            Type::uchar c = u'\x00A9'; // Copyright character '©'
            assertEquals(String::valueOf(u"©"), String::valueOf(c));
        }

    };

    CLASS_BASE (StringTest, TestCase)
    TEST (testValueOf_uchar)

    static TestSuite suite() {
        TestSuite tests = new TestSuite::Value();
        tests.addTest(new testValueOf_uchar());
        return tests;
    }
};

}
}
