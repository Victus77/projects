import Includes.*;

public class DriverCode {
    public static void main(String[] args) {
        LibraryStorage ls = new LibraryStorage();

        // Pushing to RequestQueue and testing that length is updated.
        ls.push(100001, 1);
        ls.push(100020, 2);
        ls.push(100010, 3);
        ls.push(100010, 4);
        ls.push(100006, 5);

        System.out.println(ls.rqQueueToString());

        // Processing
        boolean resp;
        for (int i=0; i<5; i++) {
            resp = ls.processQueue();
            System.out.println(resp);
            if (!resp) System.out.println(ls.prLinkedListToString());
        }

        System.out.println(ls.rqQueueToString());
    }
}
