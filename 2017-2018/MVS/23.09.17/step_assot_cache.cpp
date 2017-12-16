#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

const int BLOCK_SIZE = 1024;

double readByBlock(int * data, int n, int cnt, int block_size = BLOCK_SIZE)
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for (int j = 0; j < n; j += block_size) {
        int s = 0;
        for (int k = j; k < j + cnt; ++k) {
            s += data[k];
        }

    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto timeElapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
//    std::cout << "time difference = " << timeElapsed <<std::endl;
    return timeElapsed;
}

// Get the median of an unordered set of numbers of arbitrary
// type (this will modify the underlying dataset).
template <typename It>
auto Median(It begin, It end)
{
    const auto size = std::distance(begin, end);
    std::nth_element(begin, begin + size / 2, end);
    return *std::next(begin, size / 2);
}

void readDataBlocks()
{
    int n = 1 << 27;
    int * data = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; ++i) {
        data[i] = rand() % 100;
    }
#ifdef DEBUG
    std::cout << "L1 cache_size = 32KB" << endl;
    std::cout << "array_size = " << n << endl;
#endif
    for (int cnt = 1; cnt <= 30; ++cnt) {
#ifdef DEBUG
        std::cout << "cnt = " << cnt << endl;
#endif
        std::vector<double> secs;
        int m = 100;
        double s = 0;
        for (int i = 0; i < m; ++i) {
            double t = readByBlock(data, n, cnt);
            secs.push_back(t);
            s += t;
        }
        s /= m;
//        double mid = Median(secs.begin(), secs.end());
//        std::cout << s << endl;
        std::cout << cnt << " " << s << endl;
    }
    free(data);
}

int main()
{
    readDataBlocks();
}
