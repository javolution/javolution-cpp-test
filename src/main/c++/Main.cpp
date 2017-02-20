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
              	Thread current = Thread::currentThread();
                System::out.println(current.getName() + " say Hello");
                Thread::sleep(1000);
                System::out.println(current.getName() + " say Bye!");
            }
        };
    };

    // By implementing Runnable interface.
    class MyRunnable : public virtual Runnable {
    public:
        MyRunnable(Value* value) : Object(value) {}
        class Value : public Object::Value, public virtual Runnable::Interface {
            void run() override {
            	Thread current = Thread::currentThread();
                System::out.println(current.getName() + " say Hello");
                Thread::sleep(1000);
                System::out.println(current.getName() + " say Bye!");
            }
        };
    };


    MyThread threadA = new MyThread::Value();
    MyRunnable myRunnable = new MyRunnable::Value();
    Thread threadB = Thread::newInstance(myRunnable);

    threadA.start();
    threadB.start();
	Thread main = Thread::currentThread();
    System::out.println(main.getName() + " say Hello");
    Thread::sleep(2000);
    System::out.println(main.getName() + " say Bye!");
}
