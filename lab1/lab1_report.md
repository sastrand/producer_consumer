## Sascha Strand: Lab 1 Report

### Pthreads

I like getting a chance to use `pthreads`. I've heard a lot about it, but this is my first time diving in.

### Java

In the Java example code it took about 20 runs to get an unexpected result, which seems about right. I expect this is because two threads executed the `run` command at the same time and when they both read `sum` to add their result to it, they read the same value, added the results of their computations to each of these copies, then added each copy back to the  global variable. This would mean the calculated sum would be less than the actual sum, which is what the print statement shows.

Adding a static lock works. I changed the lock to an instance variable and run the resulting program about fifty times. I didn't generate an incorrect sum, but because each thread has its own lock in this case, one certainly could arise. 

### OpenMP

There are eleven threads running here. It would make sense that we've got the ten doing work and one running the `main()`.

### MPI

The process appears to hang.

### Chapel

I'm able to run the Chapel programs using 1-3 threads in `sum2`, but using 4 or more appears to create a deadlock condition, or at least is taking much longer than I would expect.

Running with three threads, though, it generates the correct result and with a domain size of 2000 produces a correspondingly larger total sum.

### Conclusion

I like pThreads and Java the best because I already understand the language. When there are problems, I can think at the concurrency level and not second-guess my use of the language syntax or the environment setup. I imagine this is a consideration for language designers, but I am glad for this opportunity to gain some familiarity with these new languages so that in the future I can choose to use them where a more popular language's library may fall short.
