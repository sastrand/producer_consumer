//----------------------------------------------------------------------------- 
// Program code for CS 415/515 Parallel Programming, Portland State University.
//----------------------------------------------------------------------------- 

// The sum program (Chapel version 1).
//
//
config const N = 1000;	/* problem domain size */
const D = {0..N-1};
var sum: int;

proc compute(i: int): int { 
  return i*i;
}
sum = + reduce [i in D] (compute(i));
writeln("The sum of 1,2,...,1000 is ", sum, " (should be 332833500)");
