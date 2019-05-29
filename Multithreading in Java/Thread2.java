package ThreadsFunc;

public class Thread2 implements Runnable{
	ThreadsFunc.CR1 c1;
	public Thread th;
	public Thread2(ThreadsFunc.CR1 c1_init) {
		this.c1 = c1_init;
		th  = new Thread(this, "Thread2");
		th.start();
	}
	public void run() {
		System.out.println('\t'+th.getName()+" started");
		while(Sync.RunCond) {
			
			System.out.println(th.getName() + " is opening Thread1 sem");
			Sync.sem1.release();
			System.out.println(th.getName() + " is waiting for Thread1 sem");
			try {
				Sync.sem2.acquire();
			}
			catch(InterruptedException ex) {
				System.out.println("Thread2 was interrupted\n");
			}
			try {
				th.sleep(500);
			}catch(InterruptedException e) {
				System.out.println(e);
			}
			System.out.println(th.getName() + " is pushing c1");
			c1.push();
			
		}
		System.out.println(th.getName() + " out of cycle");

		Sync.var++;
//		while(Sync.var != 6) {
//			Sync.sem1.release();
//			Sync.sem2.release();
//			Sync.br.reset();
//			
//		}
		System.out.println(th.getName() + " is ended");
	}
	
}
