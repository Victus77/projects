import Includes.*;

public class RequestQueue {
    private Node<RequestData> front;
    private Node<RequestData> back;
    private int length = 0;

    public RequestData getFront() {
        return this.front.data;
    }

    public int getLength() {
        /*
         * Your code here.
         */

        return this.length;
    }

    public void push(int ISBN, int UserID) {
        /*
         * Your code here.
         */
        return;
    }

    public void pop() {      // processing needs to be done before popping, 
        /*
         * Your code here.
         */
        return;
    }

    public String toString(){
        Node<RequestData> temp = front;
        String s = "Length: " + length + "\n";
        while(temp != null){
            s+=temp.data.toString();
            temp = temp.next;
        }
        return s;
    }
}
