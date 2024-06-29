import Includes.*;

public class PendingRequests {
    private int length = 0;
    private Node<RequestData> front;
    private Node<RequestData> back;

    public boolean insert(Node<RequestData> insnode) {
        /*
         * Your code here.
         */
        return true;
    }

    public boolean delete(Node<RequestData> delnode) {
        /*
         * Your code here.
         */
        return true;
    }

    public Node<RequestData> find(int ISBN) {
        /*
         * Your code here.
         */

        Node<RequestData> nrd = null;
        return nrd;
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
