import java.util.ArrayList;

public abstract class GPMethods {
//    int pop_size;
//    double mutation_rate;
//    int total_iters;
//    int max_iter;
//    ArrayList<Integer> best_fitness;
//    ArrayList<Node> best_list;

    abstract ArrayList<Node> init_pop(int a);
    abstract int fitness(Node n);
    abstract Node individual_generator(int a);
    abstract ArrayList<Node> seleccion(ArrayList<Node> pop, ArrayList<Integer> acc_fitness);
    abstract Node mutate(Node n);
    abstract boolean termination_condition(Node n);
    abstract Node generate_child(Node parent1, Node parent2);
    abstract ArrayList<Integer> get_fitness(ArrayList<Node> pop);
    abstract ArrayList<Integer> get_acc_fitness(ArrayList<Integer> fitness);


}
