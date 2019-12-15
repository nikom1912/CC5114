import java.util.ArrayList;

public class BinaryNode extends Node{
    public BinaryNode(){
        super();
        arguments = new ArrayList<Node>(2);
        nums_arguments = 2;
    }

    public BinaryNode(MyFunction<Integer, Integer, Integer> fn){
        super(fn);
        arguments = new ArrayList<Node>(2);
        nums_arguments = 2;
    }

    public BinaryNode(Node left, Node right){
        left.parent = this;
        arguments.set(0, left);
        right.parent = this;
        arguments.set(1, right);
    }
    public BinaryNode(ArrayList<Node> args){
        if(args.size() == 2){
            arguments = args;
            for(Node n: arguments){
                n.parent = this;
            }
        }
    }

    @Override
    public void setArgs(ArrayList<Node> args){
        if(args.size() == 2){
            arguments = args;
            for(Node n: arguments){
                n.parent = this;
            }
        }
    }
}
