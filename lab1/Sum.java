//----------------------------------------------------------------------------- 
// Program code for CS 415/515 Parallel Programming, Portland State University.
//----------------------------------------------------------------------------- 

// The sum program (Java version).
//
//
class Sum extends java.lang.Thread {
  static final int N = 1000; 
  static final int P = 10; 
  static int sum = 0; 
  Object lck = new Object();

  int low, high, psum;

  Sum(int tid) {
    low = (N/P) * tid; 	 // a simplistic partition scheme
    high = low + (N/P);
    psum = 0;
  }

  int compute(int i) {
    double x = 3.14;
    for (int j=0; j<1000; j++)
      x = x * x + i;
    return i*i;
  }

  public void run() {    // this method is required
    System.out.printf("tid: %10s low: %2d high: %3d\n", Thread.currentThread().getName(), low, high);
    for (int i = low; i < high; i++)
      psum += compute(i);
    synchronized (lck) {
      sum += psum;
    }
  }

  public static void main(String[] args) {
    try {
      Sum[] threads = new Sum[P];
      for (int k=0; k<P; k++)       // create threads
        threads[k] = new Sum(k);
      for (int k=0; k<P; k++)       // start threads
        threads[k].start();
      for (int k=0; k<P; k++)       // join threads
	threads[k].join();
      System.out.println("The sum is " + sum + " (should be 332833500)");
    } catch (Exception e) {
      System.err.println(e.getMessage());
    }
  }
}

