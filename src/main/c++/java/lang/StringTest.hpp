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
            assertEquals("\x00A9", String::valueOf(c));
        }

    };

    CTOR(StringTest, Value)

    static TestSuite suite() {
        TestSuite tests = new TestSuite::Value("StringTest");
        ADD_TEST(testValueOf_wchar, tests);
        return tests;
    }
};

}
}
