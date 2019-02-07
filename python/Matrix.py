
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
        #TODO сделать вывод более корректным например добавить свойство вывода как pretty_form
        for i in self._arr:
            for j in i:
                #print(j, end="\t")
                #print("| {6.3f} ".format(j), end="")
                print("| %6.3f " % (j), end="")
            print("|", end="")
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

    def __mul__(self, other):
        if type(other) != Matrix:
            for i in range(self.row):
                for j in range(self.column):
                    self.__setitem__((i,j), self.__getitem__((i,j))*other)
            return self
        else:
            assert(self.column == other.row)
            result = Matrix(self.row, other.column)
            for i in range(self.row):
                for j_other in range(other.column):
                    new_element = 0.
                    for j in range(self.column):
                        this = self.__getitem__((i,j))
                        that = other.__getitem__((j,j_other))
                        new_element += this * that
                    result[i,j_other] = new_element
            return result

    def __rmul__(self, other):
        if type(other) == Matrix:
            print("Holly shit we use reverse multiplication in matrix mul.!!!")
            print("If you see this message: run to __rmul__ function in Matrix class and maintain it")
        return self.__mul__(other)

    def T(self):
        result = Matrix(self.column, self.row)
        for i in range(self.row):
            for j in range(self.column):
                result[j,i] = self.__getitem__((i,j))
        return result

    def __pow__(self, power):
        if power == -1:
            assert (det(self) != 0)
            # we make inverse matrix
            result = Matrix(self.row, self.column)
            F = lambda index: 1 if index%2 == 0 else -1

            for i in range(self.row):
                for j in range(self.column):
                    result[i,j] = det(self.Minor(i,j)) * F(i+j)

            result = 1./det(self) * result
            result = result.T()
            return result
        else:
            pass

    def add_row_to_row_with_term(self, row_from, row_to, coefficient):
        #self[1,1] = 666                                                         #как здорово, что оно так работает
        for j in range(self.column):
            self[row_to,j] = self[row_to,j] + coefficient * self[row_from, j]
        return self



def det(A : Matrix) -> float:
    assert(A.row == A.column)
    T = lambda x: -1 if x%2 == 1 else 1

    if A.row == 2:
        return det_2_to_2(A)
    result = 0.
    for j in range(A.column):
        result += A[0,j] * T(j) * det(A.Minor(0,j))
    return result

def det_2_to_2(A: Matrix) -> float:
    return A[0,0]*A[1,1] - A[1,0]*A[0,1]


if __name__ == "__main__":
    #test area

    print("proof addition ")
    A = Matrix([[-11,2],[3,4]])
    B = Matrix([[1,2],[3,4]])
    C = B + A
    print(C)

    print("proof determinant ")
    A = Matrix([
        [1,2,3,4],
        [-1, 0.4, 0.5, 0.4],
        [0, 10, -1, -1],
        [5,3,2,1]
    ])
    print(det(A)) #independent proof return 101.1

    print("proof number to matrix multiplication and reflect multiplication")
    A = 2 * A
    print(A)

    print("proof matrix to matrix multiplication")
    A = Matrix([[3,4],[5,6]])
    B = Matrix([[-1],[-1]])

    C = A * B
    print(C) # легко подтверждающаяся правильность

    print("proof transpoze operation")
    print(C.T())

    print("proof find inverse matrix A * A**-1 = E = A**-1 * A")
    A = Matrix([
        [1, 2, 3, 4],
        [-1, 0.4, 0.5, 0.4],
        [0, 10, -1, -1],
        [5, 3, 2, 1]
    ])

    print(A * A**-1)
    print(A**-1 * A)
    print(A**-1)








