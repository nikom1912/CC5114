import java.lang.reflect.Parameter;
import java.util.ArrayList;
import java.util.Random;
import java.util.function.Function;

public class Main {
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
        functions.add(new NodeFactory(4));

        ArrayList<Integer> allowed = new ArrayList<>();
        allowed.add(25);
        allowed.add(7);
        allowed.add(8);
        allowed.add(100);
        allowed.add(4);
        allowed.add(2);

        AST ast = new AST(functions, allowed, 0.1);
        Node n = ast.create_rec_tree(4);
        n.print();
//        System.out.println();
//        System.out.println(n.eval());
//        System.exit(0);
        NumRep nr = new NumRep(ast);
        GP gp = new GP(nr.pop_size, nr.mutation_rate, max_iters, nr);

        gp.run();
    }
}
