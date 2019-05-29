package ThreadsFunc;

import java.util.concurrent.BrokenBarrierException;

public class Thread6 implements Runnable{
	ThreadsFunc.CR1 c1;
	public Thread th;
	public Thread6(ThreadsFunc.CR1 c1_init) {
		this.c1 = c1_init;
		th  = new Thread(this, "Thread6");
		th.start();
	}
	public void run() {
		while(Sync.RunCond) {
			System.out.println(th.getName() + "is cyclic barrier await");
			try{
				Sync.br.await();
			}catch(BrokenBarrierException ex) {
			}catch(InterruptedException ex) {
			}
			System.out.println(th.getName() + "is cyclic barrier unlock");
			
			
			System.out.println(th.getName() + "is cyclic barrier await");
			try{
				Sync.br.await();
			}catch(BrokenBarrierException ex) {
			}catch(InterruptedException ex) {
			}
			System.out.println(th.getName() + "is cyclic barrier unlock");

			
			Sync.mut.lock();
			System.out.println(th.getName() + " CR2 modification");

			boolean bt = ThreadsFunc.CR2.bool_v;
		      char ct = ThreadsFunc.CR2.char_v;
		      char ct1 = 'b';
		      ct1 = (char) (ct1 + ct);
		      short st = ThreadsFunc.CR2.short_v;
		      boolean bt1 = true;
		      bt = bt1 && bt;
		      int it = ThreadsFunc.CR2.int_v + (int)st;
		      long lt = ThreadsFunc.CR2.long_v + (long)it;
		      float ft = ThreadsFunc.CR2.float_v + (float)lt;
		      double dt = ThreadsFunc.CR2.double_v + (double)ft;
		      dt = (double)dt + (double)ft;

			Sync.mut.unlock();
		}
		System.out.println(th.getName() + " out of cycle");

			Sync.var++;

			System.out.println(th.getName() + " is ended");
		
	}
}