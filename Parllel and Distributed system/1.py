import numpy as np
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
#print(xwale)
new_x = [i[:-1] for i in x] 
new_xx = [float(i) for i in new_x]
#print(new_xx)#


file2 = open("threadOutput.txt","r")
for i in file2.readlines():
	a=i.split(',')
	y.append(a[1])
#print(y)
new_y = [i[:-1] for i in y]
new_yy = [float(i) for i in new_y] 



file3 = open("ompOutput.txt","r")
for i in file3.readlines():
	a=i.split(',')
	z.append(a[1])
#print(z)
new_z = [i[:-1] for i in z] 
new_zz = [float(i) for i in new_z]



# set width of bar
w = 0.25
fig = plt.subplots(figsize =(8,12))


bar1 = np.arange(len(xwale))
bar2 =[i+w for i in bar1]
bar3 = [i+w for i in bar2]

plt.bar(bar1,new_xx,w,label="serial")
plt.bar(bar2,new_yy,w,label="thread")
plt.bar(bar3,new_zz,w,label="Openmp")

plt.xlabel("Matrix sizes")
plt.ylabel("Time in seconds")

plt.title("Different Implementation with sizes")

plt.xticks(bar1+w,xwale)
plt.legend()
plt.show()




































