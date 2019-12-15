import java.util.ArrayList;
import java.util.Random;



public class AST {
    ArrayList<NodeFactory> functions;
    ArrayList<Integer> terminals;
    double prob;
    Random r = new Random(System.currentTimeMillis());

    public AST(ArrayList<NodeFactory> allowed_functions, ArrayList<Integer> allowed_terminals, double prob_terminal){
        functions = allowed_functions;
        terminals = allowed_terminals;
        prob = prob_terminal;
    }
    public Node create_rec_tree(int depth){
        if(depth>0){
            Node f = functions.get(r.nextInt(functions.size())).buildNode();
            ArrayList<Node> args = new ArrayList<>();
            for(int i = 0; i < f.nums_arguments; i++){
                if(r.nextDouble() < prob)
                    args.add(create_rec_tree(0));
                else
                    args.add(create_rec_tree(depth - 1));
            }
            f.setArgs(args);
            return f;
        }
        else{
            return new TerminalNode(terminals.get(r.nextInt(terminals.size())));
        }
    }
}
