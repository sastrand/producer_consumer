//----------------------------------------------------------------------------- 
// Program code for CS 415/515 Parallel Programming, Portland State University.
//----------------------------------------------------------------------------- 

// A Java notify/wait demo program.
//
//
public class SignalDemo {

  // any object can server as synchronization object
  static String synObj = "synObj";

  static Runnable doNotify = new Runnable() {
      public void run() {
	String name = Thread.currentThread().getName();
	System.out.println(name + " running");
	synchronized (synObj) {
	  try {
	    synObj.notifyAll();
	  } catch (Exception e) {
	    System.err.println(e.getMessage());
	  }
	}
	System.out.println(name + " signal sent");
      }
    };

  static Runnable doWait = new Runnable() {
      public void run() {
	String name = Thread.currentThread().getName();
	System.out.println(name + " running");
	synchronized (synObj) {
	  try {
	    synObj.wait();
	  } catch (Exception e) {
	    System.err.println(e.getMessage());
	  }
	}
	System.out.println(name + " signal received");
      }
    };

  public static void main(String[] args) {
    Thread notifier = new Thread(doNotify, "Notify");
    Thread waiter1 = new Thread(doWait, "Wait 1");
    Thread waiter2 = new Thread(doWait, "Wait 2");
    try {
      waiter1.start();
      waiter2.start();
      Thread.sleep(100); // sleep for 100ms
      notifier.start();
    } catch (Exception e) {
      System.err.println(e.getMessage());
    }
  }

}
