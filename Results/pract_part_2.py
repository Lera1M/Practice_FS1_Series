import numpy as np
import math
import matplotlib.pyplot as plt
import pandas as pd
# import scipy.special as sp


def sum_lst(x):

    coefficient = 1.0
    coefficients = []
    gamma = 0.5772156649
    summ1 = gamma + math.log(math.log(x))
    summ2 = gamma + math.log(math.log(x))
    n = 0
    while n < 100:
        n += 1
        if n == 1:
            coefficient *= math.log(x)
            coefficients.append(coefficient)
        else:
            coefficient *= ((n-1)*math.log(x))/(n**2)
            coefficients.append(coefficient)

    for i in range(n):
        summ1 += (coefficients[i])

    kahan_sum = 0
    c = 0
    for i in range(n):
        y = coefficients[i] - c
        t = kahan_sum + y
        z = t - kahan_sum
        c = z - y
        kahan_sum = t

    summ2 += kahan_sum

    res = ['{:.15f}'.format(x),
           '{:.15f}'.format(summ1), '{:.15f}'.format(summ2)]
    return res


a = 10
b = 20
data = pd.DataFrame(columns=['x_i', 'sum1', 'sum2'])


delta = (b-a)/100

t = a
while t <= b:
    data.loc[len(data.index)] = sum_lst(t)
    t += delta

data['x_i'] = data['x_i'].astype(float)
data['sum1'] = data['sum1'].astype(float)
data['sum2'] = data['sum2'].astype(float)
data.to_csv('result1.csv')
