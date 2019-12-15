import matplotlib.pyplot as plt
import sys
def main():
    args = sys.argv
    print(args)
    valores = []
    f = open(args[1])
    title = f.readline()
    if len(title) > 47:
        title = title[:47]
        title += "..."
    # max = f.readline()
    title += f.readline()
    pop_size = f.readline()
    mut_rate = f.readline()
    # title += "\n Maximo fitness posible : " + max
    title += "Tamanno de la poblacion: " + pop_size
    title += "Mutation rate: " + mut_rate
    for line in f.readlines():
        valores.append(int(line))
    f.close()
    plt.plot(range(len(valores)), valores)
    plt.title(title)
    plt.ylabel('fitness')
    plt.xlabel('generacion')
    plt.show()

if __name__ == "__main__":
    main()