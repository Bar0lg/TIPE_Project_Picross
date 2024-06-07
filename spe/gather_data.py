import matplotlib.pyplot as plt
import matplotlib
import numpy as np
import sys

font = {'size' : 18}

matplotlib.rc('font', **font)

def col(arr,n):
    return [x[n] for x in arr]

def equilibrate(a,b):
    n = len(a)
    m = len(b)
    if (n<m):
        a = np.append(a,(np.zeros(m-n,dtype=float)))
        return a,b
    elif (n>m):
        b = np.append(b,(np.zeros(n-m,dtype=float)))
        return a,b
    return a,b

def g_data(filename):
    f = open(filename,"r")
    data = f.read()
    data = data.split("\n")
    data = data[:-1]
    data = [x.split(" ") for x in data]
    seeds = np.asarray(list(map(int,col(data,0))))
    valid_t = np.asarray(list(map(float,col(data,1))))
    logic_t = np.asarray(list(map(float,col(data,2))))
    algos_t = np.asarray(list(map(float,col(data,3))))
    total_t = np.asarray(list(map(float,col(data,4))))
    nb_lr = np.asarray(list(map(int,col(data,5))))
    mode = np.asarray(list(map(int,col(data,6))))
    res = {}
    res["name"] = filename.split("/")[-1]
    res["seeds"] = seeds
    res["valid_t"] = valid_t
    res["logic_t"] = logic_t
    res["algo_t"] = algos_t
    res["total_t"] = total_t
    res["nb_lr"] = nb_lr
    res["mode"] = mode

    return res

def main_2():
    all_backtrack = [g_data(x) for x in backtrack_f]
    all_backtrack_nd = [g_data(x) for x in backtrack_nd_f]
    valid_means =       np.asarray([np.mean(x["valid_t"]) for x in all_backtrack])
    valid_means_nd =    np.asarray([np.mean(x["valid_t"]) for x in all_backtrack_nd])
    algos_mean =        np.asarray([np.mean(x["algo_t"]) for x in all_backtrack])
    algos_mean_nd =     np.asarray([np.mean(x["algo_t"]) for x in all_backtrack_nd])
    n =list(map(str, range(4,22)))
    valid_means,valid_means_nd = equilibrate(valid_means,valid_means_nd)
    algos_mean,algos_mean_nd = equilibrate(algos_mean,algos_mean_nd)
    print(algos_mean,algos_mean_nd)
    width = 0.5
    multiplier = 0
    plt.cla()
    plt.bar(n,valid_means,width,label="valid_t")
    plt.bar(n,algos_mean,width,label="algo_t",bottom=valid_means)
    plt.yscale("log")
    plt.show()

def main():
    all_backtrack = [g_data(x) for x in backtrack_f]
    all_backtrack_nd = [g_data(x) for x in backtrack_nd_f]
    valid_means =       np.asarray([np.median(x["valid_t"]) for x in all_backtrack])
    valid_means_nd =    np.asarray([np.median(x["valid_t"]) for x in all_backtrack_nd])
    algos_mean =        np.asarray([np.median(x["algo_t"]) for x in all_backtrack])
    algos_mean_nd =     np.asarray([np.median(x["algo_t"]) for x in all_backtrack_nd])
    n =list(map(str, range(4,22)))
    x = np.arange(len(n))
    valid_means,valid_means_nd = equilibrate(valid_means,valid_means_nd)
    algos_mean,algos_mean_nd = equilibrate(algos_mean,algos_mean_nd)
    print(algos_mean,valid_means_nd)
    width = 0.40
    multiplier = 0
    offset = width
    plt.cla()
    plt.bar(x + offset,valid_means,width,label="Création des automates déterministes",color="orange")
    plt.bar(x+offset,algos_mean,width,label="Algorithme de backtracking avec automates déterministes",bottom=valid_means,color="red")
    offset += offset
    plt.bar(x + offset,valid_means_nd,width,label="Création des automates non-déterministes",color="black")
    plt.bar(x+offset,algos_mean_nd,width,label="Algorithme de backtracking avec automates déterministes",bottom=valid_means_nd,color="blue")
    plt.yscale("log")
    plt.title("Médiannes du temps d'exécution des algorithmes de backtracking")
    plt.ylabel("Secondes")
    plt.xlabel("Taille du graphe")
    
    plt.legend(loc='upper left')
    plt.xticks(x+width+0.20,n)
    plt.show()


def chance_g():
    all_chance = [g_data(x) for x in chance12_f]
    solved = np.asarray([np.mean(x["nb_lr"]) for x in all_chance])
    n = list(map(str,range(10,100,10)))
    plt.cla()
    plt.bar(n,solved,width=0.50,label="Cases trouvées")
    plt.legend(loc='upper left')
    plt.axhline(12*12,linestyle="--")
    plt.ylim(0,12*12+5)
    plt.ylabel("Cases trouvées")
    plt.xlabel("Probabilité qu'une case soit noire (en %)")
    plt.title("Moyennes des cases trouvées par les règles logiques dans une grille de taille 12")
    plt.show()

def comprar():
    all_data = [g_data(x) for x in backtrack_f]
    all_data_lr = [g_data(x) for x in backtrack_nd_f]

    time_data =         np.asarray([np.median(x["total_t"]) for x in all_data])
    time_data_lr =      np.asarray([np.median(x["total_t"]) for x in all_data_lr])
    time_data,time_data_lr = equilibrate(time_data,time_data_lr)
    n =list(map(str, range(4,22)))
    x = np.arange(len(n))
    width = 0.40
    offset = width
    plt.cla()
    plt.bar(x+offset,time_data,width,label="Backtracking deterministe avec regles logiques",color="blue")
    offset += offset
    plt.bar(x+offset,time_data_lr,width,label="Backtracking non deterministe avec regles logiques",color="orange")
    plt.yscale("log")
    plt.title("Comparaison du temps d'execution (médianes)")
    plt.ylabel("Secondes")
    plt.xlabel("Taille du graphe")
    
    plt.legend(loc='upper left')
    plt.xticks(x+width+0.20,n)
    plt.show()


backtrack_f = [
"../DATA/backtrack_50000_4.txt",
"../DATA/backtrack_50000_5.txt",
"../DATA/backtrack_50000_6.txt",
"../DATA/backtrack_50000_7.txt",
"../DATA/backtrack_50000_8.txt",
"../DATA/backtrack_50000_9.txt",
"../DATA/backtrack_50000_10.txt",
"../DATA/backtrack_50000_11.txt",
"../DATA/backtrack_5000_12.txt",
"../DATA/backtrack_5000_13.txt",
"../DATA/backtrack_5000_14.txt",
"../DATA/backtrack_5000_15.txt",
"../DATA/backtrack_5000_16.txt",
"../DATA/backtrack_5000_17.txt",
"../DATA/backtrack_500_18.txt",
"../DATA/backtrack_100_19.txt",
"../DATA/backtrack_100_20.txt",
"../DATA/backtrack_100_21.txt",
]

backtrack_lr_f = [
"../DATA/lr_backtrack_50000_4.txt",
"../DATA/lr_backtrack_50000_5.txt",
"../DATA/lr_backtrack_50000_6.txt",
"../DATA/lr_backtrack_50000_7.txt",
"../DATA/lr_backtrack_50000_8.txt",
"../DATA/lr_backtrack_50000_9.txt",
"../DATA/lr_backtrack_50000_10.txt",
"../DATA/lr_backtrack_50000_11.txt",
"../DATA/lr_backtrack_5000_12.txt",
"../DATA/lr_backtrack_5000_13.txt",
"../DATA/lr_backtrack_5000_14.txt",
"../DATA/lr_backtrack_5000_15.txt",
"../DATA/lr_backtrack_5000_16.txt",
"../DATA/lr_backtrack_5000_17.txt",
"../DATA/lr_backtrack_1000_18.txt",
"../DATA/lr_backtrack_100_19.txt",
"../DATA/lr_backtrack_100_20.txt"
]

backtrack_nd_f = [
"../DATA/backtrack_nd_50000_4.txt",
"../DATA/backtrack_nd_50000_5.txt",
"../DATA/backtrack_nd_50000_6.txt",
"../DATA/backtrack_nd_50000_7.txt",
"../DATA/backtrack_nd_50000_8.txt",
"../DATA/backtrack_nd_50000_9.txt",
"../DATA/backtrack_nd_50000_10.txt",
"../DATA/backtrack_nd_50000_11.txt",
"../DATA/backtrack_nd_5000_12.txt",
"../DATA/backtrack_nd_5000_13.txt",
"../DATA/backtrack_nd_500_14.txt",
"../DATA/backtrack_nd_500_15.txt",
"../DATA/backtrack_nd_50_16.txt",
"../DATA/backtrack_nd_50_17.txt",
"../DATA/backtrack_nd_50_18.txt"
]

backtrack_nd_lr_f = [
"../DATA/lr_backtrack_nd_50000_4.txt",
"../DATA/lr_backtrack_nd_50000_5.txt",
"../DATA/lr_backtrack_nd_50000_6.txt",
"../DATA/lr_backtrack_nd_50000_7.txt",
"../DATA/lr_backtrack_nd_50000_8.txt",
"../DATA/lr_backtrack_nd_50000_9.txt",
"../DATA/lr_backtrack_nd_50000_10.txt",
"../DATA/lr_backtrack_nd_50000_11.txt",
"../DATA/lr_backtrack_nd_5000_12.txt",
"../DATA/lr_backtrack_nd_5000_13.txt",
"../DATA/lr_backtrack_nd_500_14.txt",
"../DATA/lr_backtrack_nd_500_15.txt",
"../DATA/lr_backtrack_nd_50_16.txt",
"../DATA/lr_backtrack_nd_50_17.txt",
"../DATA/lr_backtrack_nd_50_18.txt"
]

chance4_f = [
"../DATA/chance_10_50000_4.txt",
"../DATA/chance_20_50000_4.txt",
"../DATA/chance_30_50000_4.txt",
"../DATA/chance_40_50000_4.txt",
"../DATA/chance_50_50000_4.txt",
"../DATA/chance_60_50000_4.txt",
"../DATA/chance_70_50000_4.txt",
"../DATA/chance_80_50000_4.txt",
"../DATA/chance_90_50000_4.txt",
]
chance6_f = [
"../DATA/chance_10_50000_6.txt",
"../DATA/chance_20_50000_6.txt",
"../DATA/chance_30_50000_6.txt",
"../DATA/chance_40_50000_6.txt",
"../DATA/chance_50_50000_6.txt",
"../DATA/chance_60_50000_6.txt",
"../DATA/chance_70_50000_6.txt",
"../DATA/chance_80_50000_6.txt",
"../DATA/chance_90_50000_6.txt",
]

chance8_f = [
"../DATA/chance_10_50000_8.txt",
"../DATA/chance_20_50000_8.txt",
"../DATA/chance_30_50000_8.txt",
"../DATA/chance_40_50000_8.txt",
"../DATA/chance_50_50000_8.txt",
"../DATA/chance_60_50000_8.txt",
"../DATA/chance_70_50000_8.txt",
"../DATA/chance_80_50000_8.txt",
"../DATA/chance_90_50000_8.txt",
]

chance10_f = [
"../DATA/chance_10_50000_10.txt",
"../DATA/chance_20_50000_10.txt",
"../DATA/chance_30_50000_10.txt",
"../DATA/chance_40_50000_10.txt",
"../DATA/chance_50_50000_10.txt",
"../DATA/chance_60_50000_10.txt",
"../DATA/chance_70_50000_10.txt",
"../DATA/chance_80_50000_10.txt",
"../DATA/chance_90_50000_10.txt",
]

chance12_f = [
"../DATA/chance_10_5000_12.txt",
"../DATA/chance_20_5000_12.txt",
"../DATA/chance_30_5000_12.txt",
"../DATA/chance_40_5000_12.txt",
"../DATA/chance_50_5000_12.txt",
"../DATA/chance_60_5000_12.txt",
"../DATA/chance_70_5000_12.txt",
"../DATA/chance_80_5000_12.txt",
"../DATA/chance_90_5000_12.txt",
]
if __name__ == "__main__":
    main()