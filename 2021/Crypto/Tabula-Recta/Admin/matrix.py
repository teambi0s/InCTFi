class Matrix:
    def __init__(self,dims , A=None) :
        self.rows = dims[0]
        self.cols = dims[1]
        if(A == None)  :
            self.M = [[0] * self.cols for i in range(self.rows)]
        else :
            self.M = A
        
    def __str__(self) :
        m = ""
        for i in range(self.rows) :
            m += str(self.M[i])+"\n"
        return m
    def __add__(self,other) :
        C = Matrix(dims = (self.rows,self.cols))
        if isinstance(other,Matrix) :
            for i in range(self.rows) :
                for j in range(self.cols) :
                    C.M[i][j] = self.M[i][j] + other.M[i][j]
        else :
            print("Not matching type")
        return C
    def __radd__(self,other) :
        return self.__add__(other)
    def __mul__(self, other) :

        if isinstance(other,Matrix) :
            C = Matrix(dims = (self.rows,other.cols))
            for i in range(self.rows) :
                for j in range(other.cols) :
                    acc = 0
                    for k in range(other.rows) :
                        acc += self.M[i][k] * other.M[k][j]
                    #print(acc)
                    C.M[i][j] = acc
        else :
            C = Matrix(dims = (self.rows,self.cols))

            for i in range(self.rows) :
                for j in range(self.cols) :
                    C.M[i][j] = self.M[i][j] * other
        return C
    def __rmul__(self,other) :
        return self.__mul__(other)

    def __getitem__(self,key) :
        if isinstance(key, tuple) :
            i = key[0]
            j = key[1]
            return self.M[i][j]
    def __setitem__(self,key,value) :
        if isinstance(key,tuple) :
            i = key[0]
            j = key[1]
            self.M[i][j] = value
    def __sub__(self,other) : 
        C = Matrix(dims = (self.rows,self.cols)) 
        if isinstance(other,Matrix) : 
            for i in range(self.rows) : 
                for j in range(self.cols) : 
                    C.M[i][j] = self.M[i][j] - other.M[i][j] 
        else : 
            print("Not matching type") 
        return C 
    def __rsub__(self,other) : 
        return self.__sub__(other)


if __name__ == "__main__" :
    A = [[-1,  5, -1], 
       [-2, 11,  7], 
       [ 1, -5,  2]] 
    A_inv = [[-57,5,-46],[-11,1,-9],[1,0,1]] 
    Unit = [[1,0,0],[0,1,0],[0,0,1]]
    A_m = Matrix((3,3),A)
    A_inv_m = Matrix((3,3), A_inv)
    Unit_m = Matrix((3,3), Unit)
    assert (A_inv_m.__mul__(A_m)).M == Unit 
    print(Unit_m)
    print("Script successful")