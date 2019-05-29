package ThreadsFunc;


public class Thread4 implements Runnable{
	ThreadsFunc.CR1 c1;
	public Thread th;
	public Thread4(ThreadsFunc.CR1 c1_init) {
		this.c1 = c1_init;
		th  = new Thread(this, "Thread4");
		th.start();
	}
	public void run() {
		try {
			th.sleep(500);
		}catch(InterruptedException e) {
			System.out.println(e);
		}
		while(Sync.RunCond) {
			System.out.println(th.getName() + " is pushing c1");
			c1.push();
			System.out.println(th.getName() + " pushed");

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