# javolution-cpp-test
Test Suite (JUnit like) for Javolution C++ 

Value-types (stack allocated) show 30x faster allocation/deallocation speed (Visual C++ 2017)

```cpp
  -- JAVOLUTION C++ TESTING --
java::lang::ObjectTest::testStandardHeap
Number of objects allocated and destroyed per second: 1.36426e+07
java::lang::ObjectTest::testFastHeap
Number of objects allocated and destroyed per second: 2.48139e+07
java::lang::ObjectTest::testStack
Number of objects allocated and destroyed per second: 9.09091e+08
java::lang::ObjectTest::testValuePassing
Cost of passing smart pointers by value: 0.0168 μs
java::lang::ObjectTest::testConstRefPassing
Cost of passing smart pointers by const reference (const&): 0.0003 μs
java::lang::StringTest::testValueOf_uchar
java::lang::ThreadTest::testExtendingThread
java::lang::ThreadTest::testRunnableThread
Number of test cases run: 8
Number of error(s) : 0
Number of failure(s) : 0
SUCCESS !
```

