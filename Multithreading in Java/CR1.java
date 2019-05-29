package ThreadsFunc;

public class CR1 {
	public static final int Max_Size = 110;
	private int buf[] = new int[Max_Size];
	private int top = 30;
	public boolean IsEmpty(){return (top <= 0) ;}
	public boolean IsFull(){
		return top >= Max_Size-1;
	}
	synchronized public int pop(){
		if(IsEmpty()) {

		return -1;
		}
		else {
		top--;
		return top;
		}
	}

	synchronized public int push(){
		if(!IsFull()) {
		
		top++;
		buf[top] = top;
		return top;
		}
		else {
			ThreadsFunc.Sync.RunCond = false;
			return -1;
		}
	}
}
