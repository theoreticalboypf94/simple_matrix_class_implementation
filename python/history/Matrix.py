"""
реализованно Фаттаховым Павлом, "во славу себе и на благо отечества" (Макиавелли)
"""

import time

def timer(function):
    def wrapper(*args, **kwargs):
        begin = time.time()
        result = function(*args, **kwargs)
        end = time.time()
        print("time in ns = ", end - begin)
        return result
    return wrapper


class MatrixError(Exception):
    """
    У нас проблема с матрицой
    """


class Vector:
    """
    это обобщенная структура - включающая в себя как вектор строку так и вектор столбец

    инициализация:
    Vector(list:[1,2,3,4,5], str:"col") - пораждает вектор столбец
    Vector(5, str:"col") - аналогично
    Vector(5)               - по умолчанию создает вектор строку
    Vector(list: [[1],[2],[3]])  -создаст вектор столбец
    """

    def __init__(self, size_or_list, mode=None):
        """kfjkefklnfknrkjrfnrjn"""
        if mode is None:
            if type(size_or_list) == int:
                # Vector(5)
                self.__arr = [0 for i in range(size_or_list)]
                self.shape = (1,size_or_list)
            else:
                if type(size_or_list[0]) == list:
                    # Vector([[1],[2]]) is a column vector
                    self.__arr = [i[0] for i in size_or_list]
                    self.shape = (len(size_or_list), 1)
                else:
                    # Vector([1,2]) is a row vector
                    self.__arr = [i for i in size_or_list]
                    self.shape = (1, len(size_or_list))
        elif mode=="col":
            if type(size_or_list) == int:
                # Vector(5, "col")
                self.__arr = [0 for _ in range(size_or_list)]
                self.shape = (size_or_list, 1)
            else:
                # Vector([1,2,3], "col"
                self.__arr = [i for i in size_or_list]
                self.shape = (len(size_or_list), 1)
        elif mode=="row":
            if type(size_or_list) == int:
                # Vector(5, "row")
                self.__arr = [0 for i in range(size_or_list)]
                self.shape = (1,size_or_list)
            else:
                # Vector([1,2,3], "row")
                self.__arr = [i for i in size_or_list]
                self.shape = (1,len(size_or_list))

        if self.shape[0] == 1:
            self.mode = "row"
        else:
            self.mode = "col"

        if type(size_or_list) == int:
            self.len = size_or_list
        else:
            self.len = len(size_or_list)

    def __str__(self):
        out = ""
        if self.mode == "row":
            for i in self.__arr:
                #print("%6.3f |"%i, end="")
                out += "%6.3f |"%i
        else:
            for i in self.__arr:
                #print("|%6.3f|"%i)
                out += "|%6.3f|\n"%i

        return out#""

    def __getitem__(self, item):
        """vector[integer]"""
        return self.__arr[item]

    def __setitem__(self, key, value):
        self.__arr[key] = value

    def __len__(self):
        return self.len

    def __add__(self, other):
        assert(self.shape[0] == other.shape[0] and self.shape[1] == other.shape[1])  # включает в себя и сравнение по модам
        result = Vector(self.len, mode=self.mode)
        for i in range(self.len):
            result[i] = self[i] + other[i]
        return result

    def __rmul__(self, other):
        assert(type(other) != Vector)
        result = Vector(self.len, self.mode)
        for i in range(self.len):
            result[i] = other*self[i]
        return result

    def __mul__(self, other):
        if type(other) == Vector:
            if self.mode == "row":
                #dot product
                assert(self.len == other.len and other.mode == "col")
                resutl = 0;
                for i in range(self.len):
                    result += self[i] * other[i]
                return result
            else:
                # умножение столбца на строку - порождает матрицу - список векторов строк
                assert(other.mode == "row")
                result = []
                for i in range(self.len):
                    loop = Vector(other.len, "row")
                    for j in range(other.len):
                        loop[j] = self[i]*other[j]
                    result.append(loop)
                return result

        else:
            return self.__rmul__(other)

    def __iter__(self):
        for i in self.__arr:
            yield i             #аналог return но не прерывает выполнения программы


class Matrix():
    """
    Matrix(5,5)
    Matrix([[1,2,3],
            [4,5,6]
            ]
    """
    def __init__(self, a, b = None):
        self.__arr = []
        if type(a) == int:
            self.__arr = [Vector(b,"row") for _ in range(a)]
            self.shape = (a,b)
        else:
            for i in a:
                self.__arr.append(Vector(i, "row"))
            self.shape =  (len(a), len(a[0]))


if __name__ == "__main__":
    v = Vector([1,2,3],"col")
    a = (str(v))
    print(a)










