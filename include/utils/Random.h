#ifndef RANDOM_H
#define RANDOM_H
#include <vector>
#include <random>

namespace Utils {
    struct Random {
        static float random_float(float min, float max);
        static int random_int(int min, int max);

        template <typename T>
        static T random_from_enum(const std::vector<T> &elements) {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            std::uniform_int_distribution<size_t> dist(0, elements.size() - 1);

            size_t randomIndex = dist(gen);

            return elements[randomIndex];
        };
    };
}




#endif //RANDOM_H
