import java.util.*;

public class NumRep extends GPMethods {
    int numToFind = 65346;
    int pop_size = 10;
    double mutation_rate = 0.3;
    int max_depth = 17;
    AST ast;
    Random r = new Random(System.currentTimeMillis());

    NumRep(AST ast){
        this.ast = ast;
    }
    @Override
    ArrayList<Node> init_pop(int a) {
        ArrayList<Node> ar = new ArrayList<>(a);
        for(int i = 0; i < a; i++){
            Node as = ast.create_rec_tree(max_depth);
            ar.add(as);
        }
        return ar;
    }

    @Override
    int fitness(Node n) {
        int tam = n.countNodes();
        int fitness_tam =(int) (((Math.pow(2, max_depth) - tam)/Math.pow(2, max_depth))*numToFind);
        int fitnes_val = Math.max(numToFind - Math.abs(numToFind - n.eval()), 0);
        return  fitnes_val + fitness_tam;
    }

    @Override
    Node mutate(Node n) {
        ArrayList<Node> ar = n.serialize();
        int aux_depth = r.nextInt(7);
        int ran = r.nextInt(ar.size());
        Node n_aux = ast.create_rec_tree(aux_depth);
        if (ran == 0) {

            return n_aux;
        }
        Node n2 = ar.get(ran);
        n2.replace(n_aux);
        return n2;
    }

    @Override
    Node generate_child(Node parent1, Node parent2) {
        Node new_element = parent1.copy();
        Node new_element2 = parent2.copy();
        ArrayList<Node> ar1 = new_element.serialize();
        int ran1 = r.nextInt(ar1.size());
        Node p1 = ar1.get(ran1);
        ArrayList<Node> ar2 = new_element2.serialize();
        int ran2 = r.nextInt(ar2.size());
        Node p2 = ar2.get(ran2);
        if(ran1 == 0 && ran2 == 0) {
            if (fitness(p1) > fitness(p2)) {
                return p1;
            }
            return p2;
        }
        else if(ran1 == 0){
            p2.replace(p1);
            if(fitness(p2) > fitness(new_element2)) {
                return p2;
            }
            return p1;
        }
        p1.replace(p2);
        p2.replace(p1);
        if(fitness(new_element) > fitness(new_element2))
            return new_element;
        return new_element2;
    }

    @Override
    Node individual_generator(int a) {
        return ast.create_rec_tree(a);
    }

    @Override
    boolean termination_condition(Node n) {
        return (n.eval() - numToFind) == 0;
    }

    @Override
    ArrayList<Integer> get_fitness(ArrayList<Node> pop) {
        ArrayList<Integer> fitness_arr = new ArrayList<>();
        for(Node n: pop){
            fitness_arr.add(fitness(n));
        }
        return fitness_arr;
    }

    private int get_random_index(ArrayList<Integer> acc_fitness){
        int sum_total = acc_fitness.get(acc_fitness.size() - 1);
        int ran = r.nextInt(sum_total + 1);
        for(int i = 0; i < acc_fitness.size(); i++){
            if(ran <= acc_fitness.get(i)){
                return i;
            }
        }
        return acc_fitness.size() - 1;
    }
    @Override
    ArrayList<Node> seleccion(ArrayList<Node> pop, ArrayList<Integer> acc_fitness) {
        ArrayList<Node> selected = new ArrayList<>();
        for(Node n: pop){
            int index = get_random_index(acc_fitness);
            selected.add(pop.get(index));
        }
        return selected;
    }

    @Override
    ArrayList<Integer> get_acc_fitness(ArrayList<Integer> fitness) {
        int acc = 0;
        ArrayList<Integer> acc_fitness = new ArrayList<>();
        for(Integer i: fitness){
            acc += i;
            acc_fitness.add(acc);
        }
        return acc_fitness;
    }
}
