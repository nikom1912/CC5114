import java.util.ArrayList;
import java.util.Random;

public class GP {
    int pop_size;
    double mutation_rate;
    int total_iters;
    int max_iter;

    GPMethods m;
    ArrayList<Integer> besto_finess;
    ArrayList<Node> besto_nodes_list;

    Random r = new Random(1234);

    GP(int pop_size, double mutation_rate, int max_iter, GPMethods m){
        this.pop_size = pop_size;
        this.max_iter = max_iter;
        this.m = m;
        this.mutation_rate = mutation_rate;
        besto_finess = new ArrayList<>();
        besto_nodes_list = new ArrayList<>();
    }

    void run(){
        ArrayList<Node> pop = m.init_pop(pop_size);
        int iter = 0;
        ArrayList<Integer> fitness_list = m.get_fitness(pop);
        Utils.ordenarArray(fitness_list, pop);
        ArrayList<Integer> acc_fitness = m.get_acc_fitness(fitness_list);
        Node best = pop.get(pop.size() - 1);
        besto_finess.add(m.fitness(best));
        besto_nodes_list.add(best);
        long ini , fin;
        while(!m.termination_condition(best) && iter < max_iter){
            ini = System.currentTimeMillis();
            ArrayList<Node> selected = m.seleccion(pop, acc_fitness);
            for(int i = 0; i < pop_size; i++){
                Node child;
                Node parent1, parent2;
                if(i == pop_size - 1) {
                    parent1 = selected.get(i);
                    parent2 = selected.get(0);
                    child = m.generate_child(parent1, parent2);
                }
                else {
                    parent1 = selected.get(i);
                    parent2 = selected.get(i + 1);
                    child = m.generate_child(parent1, parent2);
                }

                if(r.nextDouble() < mutation_rate)
                    child = m.mutate(child);
//                System.out.println("----------------   " + child.eval());
                child.parent = null;
                pop.set(i, child);
            }
            fitness_list = m.get_fitness(pop);
            Utils.ordenarArray(fitness_list, pop);
            best = pop.get(pop_size - 1);
            besto_nodes_list.add(best);
            besto_finess.add(fitness_list.get(pop_size - 1));
            acc_fitness = m.get_acc_fitness((fitness_list));
            fin = System.currentTimeMillis();
            iter++;
            System.out.print("Best response GEN " + iter + " : " + best.eval() + "   tamanno: " + best.countNodes() + "    fit: " + m.fitness(best) + "      ");
//            best.print();
            System.out.println();
        }
        best.print();
        total_iters = iter;

    }

    ArrayList<Integer> get_list_best_fitness(){
        return besto_finess;
    }

    ArrayList<Node> getBesto_nodes_list(){
        return besto_nodes_list;
    }

    int getIters(){
        return total_iters;
    }
}
