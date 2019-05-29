package ThreadsFunc;


public class Thread5 implements Runnable{
	ThreadsFunc.CR1 c1;
	public Thread th;
	public Thread5(ThreadsFunc.CR1 c1_init) {
		this.c1 = c1_init;
		th  = new Thread(this, "Thread5");
		th.start();
	}
	public void run() {
		while(Sync.RunCond) {
			//if (!c1.IsEmpty()){
			System.out.println(th.getName() + " is poping c1");
			int tp = c1.pop();
			}
		//}
		System.out.println(th.getName() + " out of cycle");
			Sync.var++;
			System.out.println(th.getName() + " is ended");
	}

}
