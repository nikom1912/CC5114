import com.sun.jdi.connect.Connector;


import java.util.ArrayList;
import java.util.HashMap;
import java.util.Set;

public class Node {
    int nums_arguments;
    ArrayList<Node> arguments;
    Node parent;
    MyFunction<Integer, Integer, Integer> operation;

    public Node(){
        arguments = new ArrayList<>();
        nums_arguments = 0;
        parent = null;
    }

    public Node(MyFunction<Integer, Integer, Integer> fn){
        this();
        operation = fn;
    }
    public Node(ArrayList<Node> args){
        arguments = args;
        nums_arguments = args.size();
        parent = null;
    }

    public ArrayList<Node> serialize(){
        ArrayList<Node> ar = new ArrayList<Node>();
        ar.add(this);
        if(nums_arguments > 0){
            for(Node n: arguments){
                ar.addAll(n.serialize());
            }
        }
        return ar;
    }

    public Node copy(){
        Node n = new Node();
        n.operation = operation;
        n.nums_arguments = nums_arguments;
        if(nums_arguments > 0){
            n.arguments = new ArrayList<Node>();
            for(Node a: arguments){
                Node newN = a.copy();
                newN.parent = n;
                n.arguments.add(newN);
            }
        }
        n.parent = parent;
        return n;
    }

    public void replace(Node n){
        if(parent == null){
            arguments = n.arguments;
            nums_arguments = n.nums_arguments;
        }
        else{
            ArrayList<Node> a = this.parent.arguments;
            for(Node n_a : a){
                if(n_a == this){
//                    System.out.println("holiaaaaa");
                    n.parent = this.parent;
                }
            }
        }
    }

    public void addArg(Node n){
        n.parent = this;
        arguments.add(n);
        nums_arguments++;
    }

    public int countNodes(){
        int res = 1;
        if(nums_arguments > 0){
            for(Node n: arguments){
                res += n.countNodes();
            }
        }
        return res;
    }

    public void setArgs(ArrayList<Node> args){
        arguments = args;
        nums_arguments = args.size();
        for(Node n: arguments){
            n.parent = this;
        }
    }

    public int eval() throws ArithmeticException{
        int res = 0;
        for(Node n: arguments){
            res = operation.apply(res, n.eval());
        }
        return res;
    }

    public boolean noReapetTerminals(Set<Integer> term){
        boolean aux = true;
        for(Node n: arguments){
            aux = aux && n.noReapetTerminals(term);
        }
        return aux;
    }

    public void print(){
    }

}
