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

        void testValueOf_wchar() {
            Type::wchar c = L'\x00A9'; // Copyright character '©'
            assertEquals(L"\x00A2", String::valueOf(c));
        }

    };

    CTOR (StringTest, Value)
    TEST (testValueOf_wchar)

    static TestSuite suite() {
        TestSuite tests = new TestSuite::Value("StringTest");
        tests.addTest(new testValueOf_wchar());
        return tests;
    }
};

}
}
