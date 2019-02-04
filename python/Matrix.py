
class Matrix:

    def __init__(self, a, b=None):
        """
        :param a: может быть либо int or list
        :param b: в одном случае либо отсутствует либо является int

        конструктор работает в двух режимах:
        1) на вход подается 2 целвых числа, и формируется матрица заполненная нулями
        2) на вход подается список списков, который затем превращается в матрицу, второй аргумент не подается вообще

        A = Matrix(3,4)
        B = Matrix([[1,2,3,4],[5,6,7,8],[9,1,2,3]]
        """
        if type(a) is int:
            self.row = a
            self.column = b
            self._arr = [[0]*b for i in range(a)]  #тут очень интересная тема [[0]*4]*4 делать нельзя тк, все элементы будут ссылками на первый (первый список a[0])
        else:
            self.row = len(a)
            self.column = len(a[0])
            self._arr = a


    def __setitem__(self, key, value):
        x, y = key
        self._arr[x][y] = value

    def __getitem__(self, item):
        x, y = item
        return self._arr[x][y]

    def __str__(self):
        for i in self._arr:
            for j in i:
                print(j, end="\t")
            print()
        return ""

    def __add__(self, other):
        assert(self.row == other.row and self.column == other.column)
        result = Matrix(self.row, self.column)
        for i in range(self.row):
            for j in range(self.column):
                result[i,j] = self._arr[i][j] + other[i,j]
        return result

    def Minor(self, I, J):
        minor = Matrix(self.row-1, self.column-1)
        for i in range(self.row):
            for j in range(self.column):
                if (i == I or j == J):
                    continue
                minor[i if i < I else i-1,j if j < J else j-1] = self._arr[i][j]   #so butiful code organisation  value1 if condition else value2 , so amazing so convinient
        return minor

def det(A : Matrix) -> float:
    T = lambda x: -1 if x%2 == 1 else 1
    pass

def det_2_to_2(A: Matrix) -> float:
    return A[0,0]*A[1,1] - A[1,0]*A[0,1]

A = Matrix([[-11,2],[3,4]])
#print(A.Minor(1,1))
B = Matrix([[1,2],[3,4]])
C = B + A
print(C)



