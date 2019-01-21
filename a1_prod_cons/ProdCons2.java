//----------------------------------------------------------------------------- 
// ProdCons1
// A Java class that creates one producer and one consumer
// that operate concurrently over a shared buffer
// Sascha Strand
// (c) 2019
//----------------------------------------------------------------------------- 

import java.util.*;

public class ProdCons2 {
  private static final String synObj = "synObj";
  private static Queue<Integer> buf = new LinkedList<>();
  private static final Integer CAP = 20;
  private static Integer numCons = 1;
  private static Integer consumedGlobalCount = 0;
  private static String [] consumerCounts = new String[1000];

  @SuppressWarnings("Duplicates")
  static private Runnable doProducer = new Runnable() {
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

  static private Runnable doConsumer = new Runnable() {
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
            if (!end) {
              i = buf.remove();
              consumedGlobalCount = consumedGlobalCount + 1;
              consumerCounts[tid] = consumerCounts[tid] + 1;
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
        if (end) break;
      }
    }
  };

  private static Integer getNumCons(String[] args) {
    String usingDefault = "Using the default number of consumers, 1.";
    if (args.length < 1) {
      System.out.println(usingDefault);
      return 1;
    } else if (args.length > 1) {
      System.out.println("Please supply only one argument.\n" + usingDefault);
      return 1;
    } else {
      Integer numCons = Integer.parseInt(args[0]);
      if (numCons > 1 && numCons < 1000) {
        return numCons;
      } else {
        System.out.println("Please supply a number of consumers greater than 1 and less than 1000.\n"
                           + usingDefault);
      }
    }
    return 1;
  }

  private static void printConsumerCounts() {
    Integer sum = 0;
    for (int i=0;i<numCons;i++) {
      if (i<numCons-1) {
        System.out.printf("C[%d]:%d, ", i, -1);
      } else {
        System.out.printf("C[%d]:%d\n", i, -1);
      }
      //sum = sum + Integer.parseInt(consumerCounts[i]);
    }
  }

  public static void main(String[] args) {
    numCons = getNumCons(args);
    ArrayList<Thread> threads = new ArrayList<>();
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
      for (int i = 0; i < numCons; i++) {
        threads.get(i).join();
        System.out.printf("Joined %d\n", i);
      }
      printConsumerCounts();
    } catch (Exception e) {
      System.err.println(e.getMessage());
    }
    System.out.println("Main: all done!");
  }

}
