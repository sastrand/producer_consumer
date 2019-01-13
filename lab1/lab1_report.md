## Sascha Strand: Lab 1 Report

I like getting a chance to use `pthreads`. I've heard a lot about it, but this is my first time diving in.

In the Java example code it took about 20 runs to get an unexpected result, which seems about right. I expect this is because two threads executed the `run` command at the same time and when they both read `sum` to add their result to it, they read the same value, added the results of their computations to each of these copies, then added each copy back to the  global variable. This would mean the calculated sum would be less than the actual sum, which is what the print statement shows.

Adding a static lock works. I changed the lock to an instance variable and run the resulting program about fifty times. I didn't generate an incorrect sum, but because each thread has its own lock in this case, one certainly could arise. 


