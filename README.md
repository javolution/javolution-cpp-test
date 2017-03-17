# javolution-cpp-test
Test Suite (JUnit like) for Javolution C++ 

Value-types show 14x allocation/deallocation speed (Visual C++ 2015)

```cpp
 -- JAVOLUTION C++ TESTING --
java::lang::ObjectTest::testStandardHeap
Number of objects allocated and destroyed per second: 1.14416e+07
java::lang::ObjectTest::testFastHeap
Number of objects allocated and destroyed per second: 1.001e+07
java::lang::ObjectTest::testStack
Number of objects allocated and destroyed per second: 1.5873e+08
java::lang::StringTest::testValueOf_uchar
java::lang::ThreadTest::testExtendingThread
java::lang::ThreadTest::testRunnableThread
Number of test cases run: 6
Number of error(s) : 0
Number of failure(s) : 0
SUCCESS !
```

