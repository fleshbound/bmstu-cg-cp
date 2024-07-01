#include <codecvt>
#include <experimental/random>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <locale>
#include <memory>
#include <stdlib.h>
#include <string>
#include <vector>
#include <QApplication>
#include <QPixmap>
#include "scene/scene.h"

#define TEST_ITERS 20
#define TEST_MAX_DIFF 100
#define TEST_DIFF_STEP 10
#define TEST_FILE "../test_res_1.txt"

int main(int argc, char* argv[])
{
    std::wcout << L"TESTING" << std::endl;

    QApplication a(argc, argv);
    std::shared_ptr<QPixmap> _scene = std::make_shared<QPixmap>(1000, 900);
    std::wofstream file(TEST_FILE);

    if (!file.is_open())
        throw "test file error";

    for (size_t i = 0; i <= TEST_MAX_DIFF; i += TEST_DIFF_STEP)
    {
        Scene scene(_scene);
        size_t all_time = 0;

        for (size_t j = 0; j < TEST_ITERS; j++)
        {
            double cur_diffuse = double(i) / 100;
            QVector3D color(0.4, 0.4, 0.4);
            QVector3D refl = QVector3D(1, 1, 1) - QVector3D(cur_diffuse, cur_diffuse, cur_diffuse);
            double polish = 100;
            scene.change_mirror_material(refl, polish, color);
            //scene.move_light(QVector3D(i * 20, j * 20, 0));
            uint64_t start, end;
            start = clock();
            scene.draw();
            end = clock();
            uint64_t time = end - start;
            all_time += time;
            std::wcout << i << ' ' << j << ' ' << time << std::endl;
        }

        file << std::setprecision(3) << std::fixed << all_time / double(TEST_ITERS) << std::endl;
    }

    a.exit();
}
