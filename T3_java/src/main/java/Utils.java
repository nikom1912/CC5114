import java.util.ArrayList;

public class Utils {


    public static void ordenarArray(ArrayList<Integer> array, ArrayList<Node> pop){
        int temporal;
        Node temp2;
        for(int i = 0; i < pop.size(); i++){
            for(int j = 0; j < pop.size() - 1; j++){
                if(array.get(j) > array.get(j + 1)){
                    temporal = array.get(j);
                    temp2 = pop.get(j);
                    array.set(j, array.get(j + 1));
                    pop.set(j, pop.get(j + 1));
                    array.set(j + 1, temporal);
                    pop.set(j + 1, temp2);
                }
            }
        }
    }
}
