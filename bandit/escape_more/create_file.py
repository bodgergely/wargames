import sys

if __name__ == "__main__":
    num_cols = int(sys.argv[1])

    f = open('text.txt', 'w')
    i = 0

    while i < num_cols:
        f.write(str(i) * 10)
        f.write('\n')
        i+=1

    f.flush()
    f.close()



