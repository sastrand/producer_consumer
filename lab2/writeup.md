## Sascha Strand: CS 515 Parallel Programming Lab 2


### 1. The `Pthread` Sum Program

This was pretty straight-forward, walking through the examples on the slides.

I am impressed how many CPUs we can have allocated to us running on the school's machines. In this case, with Ada, I asked for 100 CPUs and got 12. On a linux lab machine, I got 8. And on babbage I got 30.

### 2. Condition Variables

I still need to read up on the sweet-spot use cases for condition variables. I didn't have any trouble implementing this code based on the examples on the slides. I need to pin down when a semaphore is the right tool and when a condition variable is the right tool.

### 3. The Java `SignalDemo` Program

Without the call to `Thread.sleep(100)` in main, the `Notify` thread may send the notify signal before the `Wait` thread has called `wait()`. This would happen if the `Notify` thread got the condition variable's lock first, sent out the notify signal, and then ended before the `Wait` thread could get the lock for the condition variable.

With two waiting threads and no sleep timer to give the waiter threads a head start, we can see the same hanging as with one thread and not sleep timer. But with a sleep timer, one of the two waiting threads will get to the condition variable first, wait, get the notification from the sender, but then end without waking up the other waiting thread.Which of the two waiting threads gets the condition variable first is non-deterministic.

With the broadcast `synObj.notifyAll()`, as long as the waiting threads are given enough of a head start to wait on the condition variable before the notify thread sends a signal, both will wake up, acquire the lock in one order or another, and run to completion.

The program will still hang if the signal from the notify thread goes out before one of the threads has made it to the call to `synObj.wait()`.

On one run I got the following output I'm not sure how to explain:

    🌲  [babbage|lab2$ java SignalDemo
    Wait 2 running
    Wait 1 running
    Notify running
    Wait 1 signal received
    Notify signal sent
    Wait 2 signal received

### 4. The Pthread Barrier Program

In the code as written, each thread running in the main changes one value in the global array `a` to the value that is to its right (wrapping around from the last position).. The main thread waits for each to end at the call to `join()`, prints `a` and terminates.

There is of course a race condition present here, but as the values in `a` are all the same at the start, this isn't apparent in the output.

I added some print statements that support this interpretation of what's going on in the code.

Adding barriers acomplishes the same result as the join() in this case. The output is the same, and that meets my expectations.

I did have some compiling trouble adding the barrier. Based on the solution in [this SO discussion](https://stackoverflow.com/questions/15673492/gcc-compile-fails-with-pthread-and-option-std-c99), I changed the language standard from `c99` to `gnu99` to access the pthread barrier struct and methods.
