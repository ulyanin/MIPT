//
// Created by ulyanin on 28.10.17.
//

#ifndef INC_28_10_2017_KR_LIFE_GAME_H
#define INC_28_10_2017_KR_LIFE_GAME_H

#include <vector>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <chrono>
#include <omp.h>


typedef std::vector<std::vector<char>> fieldType;

void genRandomField(fieldType &field, int fieldSize)
{
    for (int i = 0; i < fieldSize; ++i) {
        for (int j = 0; j < fieldSize; ++j) {
            if (rand() % 2 == 0) {
                field[i][j] = 1;
            }
        }
    }
}

int move_[][2] = {
        {1, 0},
        {1, 1},
        {0, 1},
        {-1, 1},
        {-1, 0},
        {-1, -1},
        {0, -1},
        {1, -1}
};

int numMod(int a, int b)
{
    return (a % b + b) % b;
}

void doStep(fieldType fields[2], int fieldSize, int step, const std::string &mode)
{
    int tid;
#pragma omp parallel shared(fieldSize) private(tid) num_threads(4)

//    tid = omp_get_thread_num();
#pragma omp for schedule (static)
    for (int i = 0; i < fieldSize; ++i) {
        for (int j = 0; j < fieldSize; ++j) {
            int cnt = 0;
            for (int k = 0; k < 8; ++k) {
                int ni = numMod(i + move_[k][0], fieldSize);
                int nj = numMod(j + move_[k][1], fieldSize);
                cnt += fields[step ^ 1][ni][nj];
            }
            if (!fields[step ^ 1][i][j]) {
                // dead
                fields[step][i][j] = (cnt == 3);
            } else {
                // alive
                fields[step][i][j] = (cnt == 2) || (cnt == 3);
            }
        }
    }
}

void print(const fieldType &field, int fieldSize, const std::string &mode)
{
    if (mode == "SPEED_TEST") {
        return;
    }
    system("clear");
    for (int i = 0; i < fieldSize; ++i) {
        for (int j = 0; j < fieldSize; ++j) {
            printf("%c", (field[i][j] ? 'x' : ' '));
        }
        printf("\n");
    }
}

void doSteps(fieldType &field, int fieldSize, const std::string &mode)
{
    int generations = 0;
    fieldType fields[2];
    fields[0] = fields[1] = field;
    auto begin = std::chrono::steady_clock::now();
    int num_iter = 1000;
    for (generations = 0; generations < num_iter + 1; ++generations) {
        print(fields[generations & 1], fieldSize, mode);
        doStep(fields, fieldSize, generations & 1, mode);
        if (mode == "VISUAL") {
            usleep(100000);
        }
        if (mode == "SPEED_TEST" && generations % num_iter == 0) {
            auto end = std::chrono::steady_clock::now();
            auto timeElapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
            std::cout << "time per " << num_iter << " iters = " << timeElapsed / (1e6) << std::endl;
            begin = end;
        }
    }
}

void do_life_game(int fieldSize, const std::string &mode)
{
    fieldType field(
            fieldSize,
            std::vector<char>(fieldSize, 0)
    );
    genRandomField(field, fieldSize);
    print(field, fieldSize, mode);
    doSteps(field, fieldSize, mode);
}

#endif //INC_28_10_2017_KR_LIFE_GAME_H
