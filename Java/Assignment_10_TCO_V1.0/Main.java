import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    public static <E extends Comparable<E>> void sort(ArrayList<E> list) {
        int i = 0;
        int j;
        E temp;
        int size = list.size();
        int largest;
        while (i != size-1) {
            //find biggest number from i to size
            j = i+1;
            largest = i;
            while(j < size){
                if (list.get(j).compareTo(list.get(largest)) > 0)//compare list of j with largest (if list is bigger then list equals largest
                    largest = j;
                j++;
            }
            //swap biggest with index i
            if (largest != i) {
                temp = list.get(i);
                list.set(i, list.get(largest));
                list.set(largest, temp);
            }
            //increment i
            i++;
        }

    }

    public static <E extends Comparable<E>> void print(ArrayList<E> list){
        int i = 0;
        while (i < list.size()){
            System.out.println(list.get(i++));
        }
    }

    public static void main(String[] args) {
        System.out.println("Gimme an array size, sir");
        Scanner input = new Scanner(System.in);
        int size = input.nextInt();
        ArrayList<Integer> al = new ArrayList<>(size);
        int i = 0;
        while (i < size){
            System.out.println("Gimme int "+ (i+1)+ ", sir");
            int in = input.nextInt();
            al.add(in);
            i++;
        }
        System.out.println("thank you kind sir.");
        System.out.println("you gave me this array:");
        print(al);
        System.out.println("I have sorted it in descending order.");
        sort(al);
        print(al);
    }
}

