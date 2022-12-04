import numpy as np
import matplotlib.pyplot as plt

X = np.loadtxt("Naive.1024.1000.txt", usecols=0, unpack=True)

Y_N_cc = np.loadtxt("Naive.1024.1000.txt", usecols=1, unpack=True)
Y_N_mu = np.loadtxt("Naive.1024.1000.txt", usecols=2, unpack=True)
Y_N_beta = np.loadtxt("Naive.1024.1000.txt", usecols=3, unpack=True)

Y_U_cc = np.loadtxt("Unrolled.1024.1000.txt", usecols=1, unpack=True)
Y_U_mu = np.loadtxt("Unrolled.1024.1000.txt", usecols=2, unpack=True)
Y_U_beta = np.loadtxt("Unrolled.1024.1000.txt", usecols=3, unpack=True)

# plotting the line 1 points
plt.plot(X, np.sqrt(Y_N_beta), label = "Naive")
plt.plot(X, np.sqrt(Y_U_beta), label = "Unrolled (4)")
plt.xlabel('Iteration')
plt.ylabel('no units')
# plt.title('')
plt.yscale('log')
plt.legend()
plt.show()
# plt.save fig("plot.png")
