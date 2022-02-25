import random

path = "value.txt"

f = open(path,"w")

for i in range(0,256):
    # x = random.randint(-2147483648,2147483647)
    # x = hex(x) if x >= 0 else hex(x & (2**32-1))

    x = hex(i + 1)
    
    f.write(x[2:]+"\n")

f.close()