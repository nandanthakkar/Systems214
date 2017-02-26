import sys
import re

l = []

for i in range(1,len(sys.argv)):
    sub_list = re.split('[^a-zA-Z]',sys.argv[i])
    
    for j in sub_list:
        if len(j) > 0:
            l.append(j)

print(sorted(l))
