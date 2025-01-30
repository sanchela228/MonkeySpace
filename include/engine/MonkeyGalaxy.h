#ifndef MONKEYGALAXY_H
#define MONKEYGALAXY_H
#include "types/Vector3.h"

using namespace Types;

namespace Engine {
    struct MonkeyGalaxySettings {
        Vector3 size;
        int min_count_systems;
        int max_count_systems;
    };

    struct MonkeyGalaxy {
        MonkeyGalaxy generation(MonkeyGalaxySettings settings);
    };



}

#endif //MONKEYGALAXY_H
