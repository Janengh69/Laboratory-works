# first_steps
My first steps in programming in c++ language, that can be useful for next generations :)

Bus
-----------------------------------------

**Task is to design a parameterized class, a single-list list with the following interface:**
```
template <class T>
class List{
	struct ListNode{
		T data;
		ListNode * next;
		ListNode(){
			next = NULL;
		}
		ListNode( T dat ){
			data = dat;
		}
		void Print(){
			cout<<data;
		}
	};
	
public:
	typedef ListNode node_type;
	typedef _iterator<node_type> iterator;
	//constructors / destructors
	List();
	~list();
	
	//methods
	iterator begin();   //Returns an iterator addressing the first element 
	iterator end();     //Returns an iterator that addresses the location 
                        //succeeding the last element
	

	void clear();//Erases all the elements of a list.
	bool empty();//Tests if a list is empty.

	iterator find(const node_type & val);//Returns an iterator to the 
                                        // first element in a list that 
                                        //match a specified value.

	void pop_front();//Deletes the element at the beginning of a list.

	void push_front( const node_type val);  //Adds an element to the beginning 
                                            //of a list.
	void remove(const node_type val);   //Erases first element in a list that 
                                        //match a specified value.
		

	int size();//Returns the number of elements in a list.

	void splice( iterator _Where, List<T>& _Right); //Removes element from 
                                                    //the target list and inserts it in first
                                                    // position of the argument list.
	void	Print();//Dumps list into the screen
private:
	node_type *head;
	iterator *first, *last;
};
```
