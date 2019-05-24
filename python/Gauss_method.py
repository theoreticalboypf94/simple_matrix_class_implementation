#
from Matrix import Matrix, Row, det

#TODO доделать эту скучную вещь
def Gauss_Method(A: Matrix, b: list):
    """
    this method solve Ax = b task where A is matrix
    :param A:
    :param b:
    :return:
    """
    # Gauss ofrward pass
    pass



if __name__ == "__main__":
    print("kek")
    m = Matrix.initilize_by_list([[1,2],[3,4]])
    m.swap_two_rows(0,1)
    print(m)
    print(det(m))