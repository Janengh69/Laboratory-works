package Main;
public class Main {
	public static void main (String args[]) {
		ThreadsFunc.CR1 stack = new ThreadsFunc.CR1();
		ThreadsFunc.Thread1 Trd1 = new ThreadsFunc.Thread1(stack);
        ThreadsFunc.Thread2 Trd2 = new ThreadsFunc.Thread2(stack);
        ThreadsFunc.Thread3 Trd3 = new ThreadsFunc.Thread3(stack);
        ThreadsFunc.Thread4 Trd4 = new ThreadsFunc.Thread4(stack);
        ThreadsFunc.Thread5 Trd5 = new ThreadsFunc.Thread5(stack);
        ThreadsFunc.Thread6 Trd6 = new ThreadsFunc.Thread6(stack);

        try {
            Trd1.th.join();
            Trd2.th.join();
            Trd3.th.join();
            Trd4.th.join();
            Trd5.th.join();
            Trd6.th.join();
            System.out.println("All threads ended");
        }
        catch(InterruptedException ex) {
                System.out.println(ex.getMessage());
        }
    }
}
