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
  private static final String synObj = "synObj";
  private static Queue<Integer> buf = new LinkedList<>();

  @SuppressWarnings("Duplicates")
  private static Runnable doProducer = new Runnable() {
    public void run() {
      Integer CAP = 20;
      System.out.println("Producer starting");
      for (int i = 1; i <= 100; i++) {
        synchronized (synObj) {
          try {
            if (buf.size() >= CAP) {
              synObj.wait();
            }
            buf.add(i);
            synObj.notifyAll();
            System.out.printf("Producer added value %3d (qsize = %2d)\n",
                               i, buf.size());
          } catch (Exception e) {
            System.err.println(e.getMessage());
          }
        }
      }
    }
  };

  private static Runnable doConsumer = new Runnable() {
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
            System.out.printf("Value %3d consumed (qsize = %2d)\n",
                              i, buf.size());
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
      producer.join();
      System.out.println(" --< Producer joined >--");
      consumer.join();
      System.out.println(" --< Consumer joined >--");
    } catch (Exception e) {
      System.err.println(e.getMessage());
    }
  }

}
