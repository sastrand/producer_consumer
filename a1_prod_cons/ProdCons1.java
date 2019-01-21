//----------------------------------------------------------------------------- 
// ProdCons1
// A Java class that creates one producer and one consumer
// that operate concurrently over a shared buffer
// Sascha Strand
// (c) 2019
//----------------------------------------------------------------------------- 

import java.util.LinkedList;
import java.util.Queue;

public class ProdCons1 {
  static String synObj = "synObj";
  static Queue<Integer> buf = new LinkedList<Integer>();
  static Integer CAP = 20;

  @SuppressWarnings("Duplicates")
  static Runnable doProducer = new Runnable() {
    public void run() {
      System.out.println("Producer starting");
      for (int i = 1; i <= 100; i++) {
        synchronized (synObj) {
          try {
            if (buf.size() >= CAP) {
              synObj.wait();
            }
            buf.add(i);
            synObj.notifyAll();
            System.out.println("Producer added value " + i + " (qsize = " 
                              + buf.size() + ")");
          } catch (Exception e) {
            System.err.println(e.getMessage());
          }
        }
      }
    }
  };

  static Runnable doConsumer = new Runnable() {
    public void run() {
      Integer i = 0;
      Integer i_count = 0;
      System.out.println("Consumer starting");
      while (i_count < 100) {
        synchronized (synObj) {
          try {
            if (buf.size() < 1) {
              synObj.wait();
            }
            i = buf.remove();
            i_count = i_count + 1;
            synObj.notifyAll();
            System.out.println("Value " + i + " consumed");
            } catch (Exception e) {
              System.err.println(e.getMessage());
          }
        }
      }
    }
  };

  public static void main(String[] args) {
    Thread consumer = new Thread(doConsumer);
    Thread producer = new Thread(doProducer);
    try {
      consumer.start();
      Thread.sleep(100); // sleep for 1 second
      producer.start();
    } catch (Exception e) {
      System.err.println(e.getMessage());
    }
  }

}
