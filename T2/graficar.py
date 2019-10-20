import matplotlib.pyplot as plt
def main():
    valores = []
    f = open("cmake-build-debug/r1.txt")
    title = f.readline()
    if len(title) > 47:
        title = title[:47]
        title += "..."
    max = f.readline()
    title += "\n  Maximo fitness posible : " + max
    for line in f.readlines():
        valores.append(int(line))

    plt.plot(range(len(valores)), valores)
    plt.title(title)
    plt.ylabel('fitness')
    plt.xlabel('generacion')
    plt.show()

main()
