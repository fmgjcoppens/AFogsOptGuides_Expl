import numpy as np
import matplotlib.pyplot as plt

X = np.loadtxt("Naive.1024.1000000.txt", usecols=0, unpack=True)

Y_N_cc = np.loadtxt("Naive.1024.1000000.txt", usecols=1, unpack=True)
Y_N_mu = np.loadtxt("Naive.1024.1000000.txt", usecols=2, unpack=True)
Y_N_beta = np.loadtxt("Naive.1024.1000000.txt", usecols=3, unpack=True)

Y_U_cc = np.loadtxt("Unrolled.1024.1000000.txt", usecols=1, unpack=True)
Y_U_mu = np.loadtxt("Unrolled.1024.1000000.txt", usecols=2, unpack=True)
Y_U_beta = np.loadtxt("Unrolled.1024.1000000.txt", usecols=3, unpack=True)

Y_A_cc = np.loadtxt("ASM AVX.1024.1000000.txt", usecols=1, unpack=True)
Y_A_mu = np.loadtxt("ASM AVX.1024.1000000.txt", usecols=2, unpack=True)
Y_A_beta = np.loadtxt("ASM AVX.1024.1000000.txt", usecols=3, unpack=True)

# plotting the line 1 points
# plt.plot(X, Y_N_mu, label = "Naive (C++)")
# plt.plot(X, Y_U_mu, label = "Unrolled (C++)")
# plt.plot(X, Y_A_mu, label = "AVX (assembly)")
plt.plot(X, np.sqrt(Y_N_beta), label = "Naive (C++)")
plt.plot(X, np.sqrt(Y_U_beta), label = "Unrolled (C++)")
plt.plot(X, np.sqrt(Y_A_beta), label = "AVX (assembly)")
plt.xlabel('Iterations')
# plt.ylabel('no units')
# plt.title('')
# plt.yscale('log')
plt.legend()
plt.show()
# plt.save fig("plot.png")
