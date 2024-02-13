import matplotlib.pyplot as plt
import matplotlib
import numpy as np
from scipy import linalg

TEST_MAX_DIFF = 100
TEST_STEP = 10

v = []
values_t = []

values_l = [i for i in range(10, TEST_MAX_DIFF + 1, TEST_STEP)]


def get_data_from_files():
    with open("../../../qtproject/test_res_1.txt", "r") as file:
        flag = True
        first = 1.0

        for line in file.readlines():
            num = list(map(float, line.split()))[0]
            v.append(num)

    with open("../../../qtproject/test_res_1.txt", "r") as file:
        for line in file.readlines():
            num = list(map(float, line.split()))[0]
            values_t.append(num / v[len(v) - 1])


def plot_time():
    matplotlib.rcParams.update({'font.size': 18})
    matplotlib.rcParams.update({'font.family': 'Times New Roman'})
    matplotlib.rcParams.update({'figure.figsize': (10, 7)})
    matplotlib.rcParams.update({'axes.prop_cycle': matplotlib.cycler(color=['black'])})

    plt.plot(values_l, values_t, 'o')

    plt.xlabel('Коэффициент диффузного отражения, 1 * 100')
    plt.ylabel(r'Относительное время выполнения')

    ax = plt.gca()
    ax.margins(0.001)

    plt.legend(fontsize=18)

    # plt.loglog()

    plt.tight_layout()

    plt.show()

    val_t = np.array(values_t)
    val_x = np.array(values_l)
    m = len(val_x)
    X1 = np.stack((np.ones(m), val_x, val_x**6)).T

    beta1, resuaials1, _, _ = linalg.lstsq(X1, val_t)

    print(resuaials1)
    print(beta1)

    cof1, residuals1, _, _, _ = np.polyfit(val_x, val_t, 6, full=True)
    print(cof1)
    print(residuals1)
    p1 = np.poly1d(cof1)
    y_t = p1(val_x)
    
    plt.plot(values_l, y_t, label='Апроксимация')
    plt.plot(values_l, values_t, 'o', label='Исходные данные')
    ax = plt.gca()
    ax.margins(0.001)

    plt.legend(fontsize=18)

    # plt.loglog()
    plt.xlabel('Коэффициент диффузного отражения * 100')
    plt.ylabel(r'Относительное время выполнения')
    plt.tight_layout()
    plt.show()

# def plot_mem():
#     plt.plot(values_l, values_m[1], linestyle='solid', label='Сортировка Шелла')
#     plt.plot(values_l, values_m[2], 'd', linestyle='solid', label='Сортировка Перемешиванием')
#     plt.plot(values_l, values_m[3], linestyle='dashed', label='Плавная Сортировка')
#
#     plt.xlabel('Количество элементов в массиве')
#     plt.ylabel(r'Память (байт)')
#
#     ax = plt.gca()
#     ax.margins(0.001)
#
#     plt.legend(fontsize=10)
#
#     plt.loglog()
#
#     plt.tight_layout()
#
#     plt.show()


get_data_from_files()
plot_time()
# plot_mem()

for i in range(len(values_t)):
     print(f'   \\num{{{i * TEST_STEP / 100}}} & \\num{{{values_t[i]}}}  \\\\\\hline')

# print('-------')
#
# for i in range(len(values_m[1])):
#     print(f'   \\num{{{i * TEST_STEP}}} &
