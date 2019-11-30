import subprocess
import matplotlib.pyplot as plt
import os
from pathlib import Path
seq_values = []
n_values = []
par_values = []
init = 1000000
compileData = "gcc -o createData gg.c".split(" ")
print(compileData)
subprocess.check_output(compileData)
for i in range(0, 100):
    fileName = str(init) + ".txt"
    file = Path(fileName)
    if not file.is_file():
        createData = ["./createData", str(init)]
        subprocess.call(createData)
    # print(fileName)
    parSt = "./par "+str(init)+" "+fileName
    process = subprocess.Popen(parSt.split(" "), stdout=subprocess.PIPE)
    parOut, err = process.communicate()
    par = (str(parOut)).split(":")[1].split("'")[0]

    seqSt = "./seq "+str(init)+" "+fileName
    process = subprocess.Popen(seqSt.split(" "), stdout=subprocess.PIPE)
    seqOut, err = process.communicate()
    # print(seqOut)
    seq = (str(seqOut)).split(":")[1].split("'")[0]
    print(init, seq, par)
    n_values.append(init)
    seq_values.append(seq)
    par_values.append(par)
    init = init+1000000
plt.plot(n_values, par_values)

# naming the x axis
plt.xlabel('Order of input (n)')
# naming the y axis
plt.ylabel('Parallel search time')

# giving a title to my graph
plt.title('Sequential search CRCW plot')

# function to show the plot
plt.show()
