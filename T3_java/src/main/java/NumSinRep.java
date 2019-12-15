import java.util.ArrayList;
import java.util.HashSet;

public class NumSinRep extends NumRep {
    NumSinRep(AST ast){
        super(ast);
    }

    @Override
    int fitness(Node n){

        int tam = n.countNodes();
        int fitness_tam =(int) (((Math.pow(2, max_depth) - tam)/Math.pow(2, max_depth))*numToFind);
        int fitnes_val = Math.max(numToFind - Math.abs(numToFind - n.eval()), 0);
        if(!n.noReapetTerminals(new HashSet<>())){
            return (fitnes_val + fitness_tam)/100;
        }
        return  fitnes_val + fitness_tam/5;
    }

}
