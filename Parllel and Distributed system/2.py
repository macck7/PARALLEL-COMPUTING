#!/usr/bin/env python
# coding: utf-8

import matplotlib.pyplot as plt
import pandas as pd


xwale=[]
x=[]
y=[]
z=[]

file1 = open("serialOutput.txt","r")
for i in file1.readlines():
	a=i.split(',')
	xwale.append(a[0])
	x.append(a[1])
new_x = [i[:-1] for i in x] 
new_xx = [float(i) for i in new_x]
#print(xwale)
#print(x)


file2 = open("threadOutput.txt","r")
for i in file2.readlines():
	a=i.split(',')
	y.append(a[1])
new_y = [i[:-1] for i in y] 
new_yy = [float(i) for i in new_y]
#print(y)


file3 = open("ompOutput.txt","r")
for i in file3.readlines():
	a=i.split(',')
	z.append(a[1])
new_z = [i[:-1] for i in z] 
new_zz = [float(i) for i in new_z]
#print(z)

fig=plt.figure(figsize=(8, 12))
plt.plot(xwale,new_xx,marker="o")
plt.plot(xwale,new_yy,marker="o")
plt.plot(xwale,new_zz,marker="o")
plt.ylabel("Time in seconds", fontsize = 16)
plt.xlabel("Matrix size", fontsize= 16)
plt.legend(["serial", "thread","openMP"])
plt.show()


