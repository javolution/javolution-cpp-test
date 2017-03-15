/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include "junit/framework/TestCase.hpp"
#include "junit/framework/TestSuite.hpp"
#include "java/lang/System.hpp"

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
					String::valueOf("Number of objects allocated and destroyed per second: ")
							+ (COUNT * 1000.0 / (end - start)));
		}

		void testFastHeap() {
			static Object vector[USAGE];
			//   Type::FastHeap::INSTANCE.setSize(2048); // Blocks.
			Type::FastHeap::INSTANCE.enable();
			Type::int64 start = System::currentTimeMillis();
			for (int i = 0; i < COUNT; i++) {
				vector[i % USAGE] = new Object::Value();
			}
			Type::int64 end = System::currentTimeMillis();
			System::out.println(
					String::valueOf("Number of objects allocated and destroyed per second: ")
							+ (COUNT * 1000.0 / (end - start)));
			Type::FastHeap::INSTANCE.disable();
			long maxUsage = Type::FastHeap::INSTANCE.getMaxUsage();
			assertTrue(maxUsage < USAGE + 40);
			System::out.println(String::valueOf("FastHeap Maximum Usage (allocated blocks): ") + maxUsage);
			System::out.println(String::valueOf("System Heap Allocations: ") +
					Type::FastHeap::INSTANCE.getSystemHeapCount());
		}
	};

	CTOR (ObjectTest, Value)
	TEST (testStandardHeap)TEST (testFastHeap)

	static TestSuite suite() {
		TestSuite tests = new TestSuite::Value();
		tests.addTest(new testStandardHeap());
		tests.addTest(new testFastHeap());
		return tests;
	}
};

}
}
