package ThreadsFunc;

import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.ReentrantLock;

public class Sync {
	public static Semaphore sem1 = new Semaphore(0, true);
	public static Semaphore sem2 = new Semaphore(0, true);
    public static ReentrantLock mut = new ReentrantLock();
    public static CyclicBarrier br = new CyclicBarrier(2);
    
    public static boolean RunCond = true;
	public static int var = 0;
}
