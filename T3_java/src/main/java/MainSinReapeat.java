import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Random;

public class MainSinReapeat {
    static Random r = new Random(System.currentTimeMillis());
    static int max_iters = 1000;
    public static void main(String[] args) {

//        int a = (int)(((Math.pow(2, 9) - 100)/Math.pow(2, 9))*10000);
//        System.out.println(a);
//        for(int i = 0; i < 70000; i++){
//            System.out.println(r.nextDouble());
//        }
        ArrayList<NodeFactory> functions = new ArrayList<>();
        functions.add(new NodeFactory(1));
        functions.add(new NodeFactory(2));
        functions.add(new NodeFactory(3));

        ArrayList<Integer> allowed = new ArrayList<>();
        allowed.add(25);
        allowed.add(7);
        allowed.add(8);
        allowed.add(100);
        allowed.add(4);
        allowed.add(2);

        AST ast = new AST(functions, allowed, 0.2);
        NumRep nr = new NumSinRep(ast);
        GP gp = new GP(nr.pop_size, nr.mutation_rate, max_iters, nr);
        gp.run();
        try {
            FileWriter fw = new FileWriter("src/main/java/p2.txt");
            PrintWriter pw = new PrintWriter(fw);
            pw.println("Grafico sin repeticion: " + nr.numToFind );
            pw.println("Respuesta: " + gp.besto_nodes_list.get(gp.getIters() - 1).eval());
            pw.println(nr.pop_size);
            pw.println(nr.mutation_rate);
            ArrayList<Integer> forGraph = gp.get_list_best_fitness();
            for(int i =0 ; i < gp.getIters(); i++){
                pw.println(forGraph.get(i));
            }
            pw.close();
            fw.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
}
