package ThreadsFunc;

public class Thread1 implements Runnable {
	ThreadsFunc.CR1 c1;
	public Thread th;
	public Thread1(ThreadsFunc.CR1 c1_init) {
		this.c1 = c1_init;
		th  = new Thread(this, "Thread1");
		th.start();
	}
		public void run() {
		System.out.println(th.getName()+" started");
		while(Sync.RunCond) {
			
			System.out.println(th.getName() + " is opening Thread2 sem");
			Sync.sem2.release();
			System.out.println(th.getName() + " is waiting for Thread2 sem");
			try {
				Sync.sem1.acquire();
			}
			catch(InterruptedException ex) {
				System.out.println("Thread_1 was interrupted\n");
			}
			
			System.out.println(th.getName() + " is pushing c1");
			c1.push();
		}
		System.out.println(th.getName() + " out of cycle");

		Sync.var++;
		while(Sync.var != 6) {
			Sync.sem1.release();
			Sync.sem2.release();
			Sync.br.reset();
			
		}
		System.out.println(th.getName() + " is ended");
	}
	
}