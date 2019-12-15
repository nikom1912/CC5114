import java.util.HashSet;

public class WithDivision extends NumRep {
    WithDivision(AST ast){
        super(ast);
        numToFind = 20000;
        mutation_rate = 0.3;

    }

    @Override
    int fitness(Node n){
        int res;
        try {
            res = n.eval();
        }
        catch (ArithmeticException e){
            return 0;
        }
        int tam = n.countNodes();
        int fitness_tam =(int) (((Math.pow(2, max_depth) - tam)/Math.pow(2, max_depth))*numToFind);
        int fitnes_val = Math.max(numToFind - Math.abs(numToFind - res), 0);
        return  fitnes_val + fitness_tam/5;
    }
}
