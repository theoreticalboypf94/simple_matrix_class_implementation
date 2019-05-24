import math
import copy

class Row:

    def __init__(self, length):
        self.row = [0] * length
        self.__len = length       #way to make it more private

    #group of interface operations
    def __getitem__(self, item):
        return self.row[item]

    def __setitem__(self, key, value):
        self.row[key] = value

    def __len__(self):
        return self.__len

    def __repr__(self):
        output = "[" + ",".join(map(str,self.row)) + "]"
        return output

    #arifmetic
    def __add__(self, other):
        assert(self.__len == other.__len)  # beyond using exceptions
        result = Row(self.__len)
        for i in range(self.__len):
            result[i] = self[i] + other[i]
        return result

    def __sub__(self, other):
        other = -1 * other
        return self + other

    def __mul__(self, other):
        result = Row(len(self))
        for i in range(len(self)):
            result[i] = self[i] * other
        return result

    def __rmul__(self, other):
        return self.__mul__(other)

    def __truediv__(self, other):
        other = 1./ other
        return self * other

    def __xor__(self, other):
        # NB this is dot product of 2 row-vector
        assert(len(self) == len(other))
        result = 0.
        for i,j in zip(self, other):
            result += i * j
        return result


    # may be useful operations
    # this function swap on i-th and j-th position
    def swap(self, i, j):
        self[i], self[j] = self[j], self[i]

    #simple factory method using for initialization of row in different way
    @classmethod
    def initilize_by_list(cls, lst: list):
        result = cls(len(lst))
        for i in range(len(result)):
            result[i] = lst[i]
        return result


class Matrix:

    def __init__(self, _rows, _columns):
        self.rows = _rows
        self.columns = _columns
        self._matrix = [Row(self.columns) for i in range(self.rows)] # construct matrix memory allocator

    # groop of interface operator

    def __getitem__(self, item):
        return self._matrix[item]

    def __len__(self):
        #return number of rows
        return self.rows

    def shape(self):
        return self.rows, self.columns

    def __repr__(self):
        output = ""
        for i in range(len(self)):
            output += self[i].__repr__() + '\n'
        return output

    #arifmetic

    def __add__(self, other):
        assert(self.shape() == other.shape())
        result = Matrix(self.rows, self.columns)
        for i in range(self.rows):
            for j in range(self.columns):
                result[i][j] = self[i][j] + other[i][j]
        return result

    def __mul__(self, other):
        if type(other) != Matrix:
            result = Matrix(self.rows, self.columns)
            for i in range(self.rows):
                for j in range(self.columns):
                    result[i][j] = self[i][j] * other
            return result
        else:
            assert(self.columns == other.rows)       #число столбцов 1го == числу строк 2го
            result = Matrix(self.rows, other.columns)
            for i in range(self.rows):
                for j in range(other.columns):
                    accamulation = 0
                    for k in range(self.columns):  # convolution
                        accamulation+= self[i][k] * other[k][j]
                    result[i][j] = accamulation
            return result

    def __rmul__(self, other):
        if type(other) != Matrix:
            return self.__mul__(other)

    def __eq__(self, other):
        print("don't work tldd")

    def __truediv__(self, other):
        result = Matrix(self.rows, self.columns)
        for i in range(self.rows):
            for j in range(self.columns):
                result[i][j] = self[i][j] / other
        return result

    def __pow__(self, power, modulo=None):
        if power > 0:
            assert(self.columns == self.rows) # work only for square matrix
            result = copy.deepcopy(self)
            for i in range(power-1):
                result = result * self;
            return result
        if power == 1:
            assert(self.columns == self.rows)
            return Matrix.create_I(self.rows)
        if power == -1:
            #начинаем искать обратную матрицу
            result = Matrix(self.rows, self.columns)
            D = det(self)
            h = lambda x: 1 if x%2 == 0 else -1
            for i in range(self.rows):
                for j in range(self.columns):
                    result[i][j] = h(i+j) * det(self.Minor(i,j))

            result = result.T()
            result = result / D
            return result



    #matrix specific operations

    def Minor(self, i, j):
        """
        return new matrix consist from all element except on line i and j
        """
        result = Matrix(self.rows-1, self.columns-1)
        for ii in range(self.rows):
            for jj in range(self.columns):
                if ii == i or jj == j:
                    pass
                else:
                    result[ii if ii<i else ii-1][jj if jj<j else jj-1] = self[ii][jj]
        return result

    def T(self):
        result = Matrix(self.columns, self.rows)
        for i in range(self.rows):
            for j in range(self.columns):
                result[j][i] = self[i][j]
        return result



    # simple factory method using for initialization of matrix in different way

    @classmethod
    def initilize_by_list(cls, list_of_list: list):
        row, column = len(list_of_list), len(list_of_list[0])
        result = cls(row, column)
        for i in range(row):
            for j in range(column):
                result[i][j] = list_of_list[i][j]
        return result

    @classmethod
    def create_I(cls, size):
        result = cls(size, size)
        for i in range(size):
            result[i][i] = 1
        return result

    @classmethod
    def create_RND_matrix(cls, row, col):
        result = cls(row,col)
        for i in range(row):
            for j in range(col):


def det2x2(m: Matrix) -> float:
    return m[0][0]*m[1][1] - m[1][0]*m[0][1]

def det(m: Matrix) -> float:
    assert(m.shape()[0] == m.shape()[1])
    amount_of_col = m.shape()[1]
    h = lambda x: 1 if x%2 == 0 else -1
    result = 0.
    if m.shape() == (2,2):
        return det2x2(m)

    for j in range(amount_of_col):
        result += h(j) * m[0][j] * det(m.Minor(0,j))
    return result





if __name__ == "__main__":
    m = Matrix.initilize_by_list([[1,1,1],
                                  [4,1,2],
                                  [0,0,9]])
    m2 = m**-1
    print(m2)
    print(m2*m)
    print(m*m2)