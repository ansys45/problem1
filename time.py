import numpy as np
import matplotlib.pyplot as plt

x, z, y = np.loadtxt("time.csv", unpack = True, delimiter = ",")
plt.plot(x, y)
plt.xlabel("Length of number")
plt.ylabel("Time in seconds")
plt.title("Time Comparison")
plt.show()