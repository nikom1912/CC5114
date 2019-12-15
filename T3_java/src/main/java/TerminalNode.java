import java.util.ArrayList;
import java.util.Set;

public class TerminalNode extends Node {

    int value;

    TerminalNode(int val){
        value = val;
        arguments = null;
        nums_arguments = 0;
    }

    @Override
    public int eval() {
        return value;
    }

    @Override
    public boolean noReapetTerminals(Set<Integer> term){
        if(term.contains(value)){
            return false;
        }
        term.add(value);
        return true;
    }

    public Node copy(){
        Node n = new TerminalNode(value);
        n.parent = parent;
        return n;
    }

    @Override
    public void print() {
        System.out.print(value);
    }
}
