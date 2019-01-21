//----------------------------------------------------------------------------- 
// ProdCons1
// A Java class that creates one producer and one consumer
// that operate concurrently over a shared buffer
// Sascha Strand
// (c) 2019
//----------------------------------------------------------------------------- 

import java.util.*;

public class ProdCons2 {
  static String synObj = "synObj";
  static Queue<Integer> buf = new LinkedList<Integer>();
  static Integer CAP = 20;
  static Integer consumedGlobalCount = 0;
  static String [] consumerCount = new String[1000];

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
      String tName = Thread.currentThread().getName();
      Integer tid = Integer.parseInt(tName);
      Integer i = 0;
      boolean end = false;
      System.out.println("Consumer[" + tName + "] starting");
      while (true) {
        synchronized (synObj) {
          try {
            while (buf.size() < 1) {
              synObj.wait();
              if (consumedGlobalCount >= 100) {
                end = true;
                synObj.notifyAll();
                break;
              }
            }
            if (end != true) {
              i = buf.remove();
              consumedGlobalCount = consumedGlobalCount + 1;
              consumerCount[tid] = consumerCount[tid] + 1;
              synObj.notifyAll();
              System.out.println("Consumer[" + Thread.currentThread().getName()
                                 + "] removed value " + i);
              if (consumedGlobalCount >= 100) {
                end = true;
                synObj.notifyAll();
              }
            }
          } 
          catch (Exception e) {
            System.err.println(e.getMessage());
          }
        }
        if (end == true) break;
      }
    }
  };

  public static void main(String[] args) {
    Integer numCons = 9;
    ArrayList<Thread> threads = new ArrayList<Thread>();
    for (int i = 0; i < numCons; i++) {
      threads.add(new Thread(doConsumer, Integer.toString(i)));
    }
    Thread producer = new Thread(doProducer);
    try {
      for (int i = 0; i < numCons; i++) {
        threads.get(i).start();
      } 
      Thread.sleep(100); // sleep for 1 second
      producer.start();
    } catch (Exception e) {
      System.err.println(e.getMessage());
    }
    System.out.println("Done!");
  }

}
