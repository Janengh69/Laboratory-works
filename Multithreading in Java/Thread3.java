package ThreadsFunc;

import java.util.concurrent.BrokenBarrierException;

public class Thread3 implements Runnable{
	ThreadsFunc.CR1 c1;
	public Thread th;
	public Thread3(ThreadsFunc.CR1 c1_init) {
		this.c1 = c1_init;
		th  = new Thread(this, "Thread3");
		th.start();
	}
	public void run() {
		while(Sync.RunCond) {
			System.out.println(th.getName() + " is cyclic barrier await");
			try{
				Sync.br.await();
			}catch(BrokenBarrierException ex) {
			}catch(InterruptedException ex) {
			}
			System.out.println(th.getName() + " CR2 modification");
			Sync.mut.lock();
			ThreadsFunc.CR2.bool_v = false;
			ThreadsFunc.CR2.short_v--;
			ThreadsFunc.CR2.char_v++;
			ThreadsFunc.CR2.long_v--;
			ThreadsFunc.CR2.float_v++;
			ThreadsFunc.CR2.double_v--;
			Sync.mut.unlock();
			System.out.println(th.getName() + " cyclic barrier await");
			try{
				Sync.br.await();
			}catch(BrokenBarrierException ex) {
			}catch(InterruptedException ex) {
			}
			System.out.println(th.getName() + " cyclic barrier unlocked");
			
		}
		System.out.println(th.getName() + " out of cycle");

			Sync.var++;

			System.out.println(th.getName() + " is ended");
		
	}
}
	
