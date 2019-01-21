# Sascha Strand: Multi-consumer/Producer in Java and C

I wasn't sure what to expect from this project. I've implemented the 
single-consumer producer problem a few times, but adding an arbitrary number of
additional consumers made it a fun challenge.

At first, I wanted to use a global variable to indicate if there were still
values available for the consumers to consume. It could work like an on-off
switch for the whole system. As I started planning this out, I realized the flag
would need to be a second condition variable, and where initially this
seemed like the sturdier solution, it started to seem like more overhead with
no obvious feature addition.

I reasoned that using an indicator value in the pipeline would be more like
how a message passing system would shut down. And that would be
simpler to implement. So I used a `-1` in the pipeline (buffer/queue) to tell
a thread that its day was done.

I didn't encounter any significant issues. The last time I wrote code in Java
was in the summer. I forgot that I like it. There's nothing like the
feeling of making the little red lines go away in IntelliJ.

