/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */

#include "java/lang/Thread.hpp"
#include "java/lang/System.hpp"

/* Unit test main routine */
int main(int, char**) {

    // By extending Thread class
    class MyThread : public virtual Thread {
    public:
        MyThread(Value* value) : Object(value) {}
        class Value : public Thread::Value {
            void run() override {
                System::out.println("Thread say Hello");
                Thread::sleep(1000);
                System::out.println("Thread say Bye!");
            }
        };
    };

    // By implementing Runnable interface.
    class MyRunnable : public virtual Runnable {
    public:
        MyRunnable(Value* value) : Object(value) {}
        class Value : public Object::Value, public virtual Runnable::Interface {
            void run() override {
                System::out.println("Runnable say Hello");
                Thread::sleep(500);
                System::out.println("Runnable say Bye!");
            }
        };
    };


    MyThread threadA = new MyThread::Value();
    MyRunnable myRunnable = new MyRunnable::Value();
    Thread threadB = Thread::newInstance(myRunnable);

    threadA.start();
    threadB.start();
    System::out.println("Wait");
    Thread::sleep(2000);
}
