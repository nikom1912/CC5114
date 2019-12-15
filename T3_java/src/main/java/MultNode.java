import java.util.ArrayList;

public class MultNode extends BinaryNode {
    public MultNode(){
        super();
        operation = (Integer a, Integer b) -> {return a *b;};
    }
    public int eval(){
        return operation.apply(arguments.get(0).eval() , arguments.get(1).eval());
    }
    public void print(){
        System.out.print("(");
        arguments.get(0).print();
        System.out.print(  " * ");
        arguments.get(1).print();
        System.out.print(")");
    }
    public Node copy(){
        Node n = new MultNode();
        n.arguments = new ArrayList<>();
        for(Node a: arguments){
            Node newN = a.copy();
            newN.parent = n;
            n.arguments.add(newN);
        }
        n.parent = parent;
        return n;
    }
}
