# Introduction

[Javolution C++ Test](https://github.com/javolution/javolution-cpp) is a "Case-Study" on how to build native executables
 (Windows or Linux) based on [Javolution C++](https://github.com/javolution/javolution-cpp) and [Maven](http://maven.apache.org/).
On top of running unit tests (JUnit like), the executable also perform benchmark tests of Javolution native solution.

# Building

## On POSIX systems (with GCC 4.8+)

1.  Install [Apache Maven](http://maven.apache.org/) on your system.
2.  Get a copy of [Javolution C++](https://github.com/javolution/javolution-cpp) and 
    [Javolution C++ Test](https://github.com/javolution/javolution-cpp-test) source code, either by cloning their 
    repository, or by downloading an archive.
3.  Run `maven install` at the root of the javolution-cpp directory.
4.  Run `maven install` at the root of the javolution-cpp-test directory, that last install will execute the tests.

## On Windows (MSVC 2015+)

1.  Download and install Visual C++ from [Visual Studio Community](https://www.visualstudio.com/vs/community/) (free).
2.  Install [Apache Maven](http://maven.apache.org/) on your system.
3.  Get a copy of [Javolution](https://github.com/javolution/javolution), 
    [Javolution C++](https://github.com/javolution/javolution-cpp) and 
    [Javolution C++ Test](https://github.com/javolution/javolution-cpp-test) source code, either by cloning their 
    repository, or by downloading an archive.
4.  Run `maven install` at the root of the javolution directory (to support MSVC native plugin).
5.  Run `maven install` at the root of the javolution-cpp directory.
6.  Run `maven install` at the root of the javolution-cpp-test directory, that last install will execute the tests.

# Test Results

Here is an example of an execution output. It shows that Javolution C++ stack allocated objects 
(small immutable objects such as numbers) are significantly faster (30x) than heap allocated objects (in standard Java
all objects even Boolean, Integer or Double are heap allocated). 
In other words, a generic math library (e.g. JScience) ported to Javolution C++ should run as fast as if primitive types
where being used (e.g. Matrix&lt;Complex&gt;), a feat not possible with current Java yet!

```
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

