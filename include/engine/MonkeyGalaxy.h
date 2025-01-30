#ifndef MONKEYGALAXY_H
#define MONKEYGALAXY_H
#include <string>

#include "types/Vector3.h"

using namespace Types;

namespace Engine {
    struct MonkeyGalaxySettings {
        Vector3 size;
        std::string seed;

        int min_count_systems = 1;
        int max_count_systems = 5;
        int min_count_entities_per_system = 1;
        int max_count_entities_per_system = 5;
        int min_count_children_per_entity = 0;
        int max_count_children_per_entity = 5;

        bool systems_without_stars = false;
        char percent_star_in_system = 80;
    };

    struct MonkeyGalaxy {
        std::vector<Entity*> entities;
        MonkeyGalaxy generate(MonkeyGalaxySettings settings);
    };

}

#endif //MONKEYGALAXY_H
