public class NodeFactory {
    int node_type;
    public NodeFactory(int type){
        node_type = type;

    }
    public Node buildNode(){
        switch (node_type){
            case 1:
                return new AddNode();
            case 2:
                return new SubNode();
            case 3:
                return new MultNode();
            case 4:
                return new MaxNode();
            case 5:
                return new DivisionNode();
        }
        return null;
    }
}
