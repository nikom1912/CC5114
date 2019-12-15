import java.util.ArrayList;

public class MaxNode extends BinaryNode {
    public MaxNode(){
        super();
        operation = Integer::max;
    }
    public int eval(){
        return operation.apply(arguments.get(0).eval(),  arguments.get(1).eval());
    }
    public void print(){
        System.out.print("max(");
        arguments.get(0).print();
        System.out.print(", ");
        arguments.get(1).print();
        System.out.print(")");
    }

    public Node copy(){
        Node n = new MaxNode();
        n.arguments = new ArrayList<Node>();
        for(Node a: arguments){
            Node newN = a.copy();
            newN.parent = n;
            n.arguments.add(newN);
        }
        n.parent = parent;
        return n;
    }
}
