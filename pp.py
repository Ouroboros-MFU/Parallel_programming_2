import numpy as np
N = 500
with open("result.txt", 'w') as file:
    for i in range(9):
        print(i)
        with open("../parapells/matrix/" + str(N) + "/A.txt", 'r') as aFile:
            A = np.loadtxt(aFile)
            aFile.close()

        with open("../parapells/matrix/" + str(N) + "/B.txt", 'r') as bFile:
            B = np.loadtxt(bFile)
            bFile.close()

    #print(A)
    #print()
    #print(B)
        matr = np.dot(A, B)

        with open("../parapells/matrix/" + str(N) + "/C.txt", 'r') as cFile:
            C = np.loadtxt(cFile)
            cFile.close()
        result = np.array_equal(matr, C)

    
        file.write(str(N) + ' ' + str(result) + '\n')
        N += 250
print("complete!")
