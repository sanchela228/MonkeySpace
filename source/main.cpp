#include <array>
#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <random>

#include "types/Vector3.h"
#include "utils/Random.h"


class Universe {

};



namespace MonkeyGalaxy {
    class Entity;
    class System;
    class Grid;

    std::string seed;

    enum class DirectionType {Orbital, Follow};

    std::map<DirectionType, std::string> mapDirectionTypeNames {
        {DirectionType::Orbital, "Orbital"},
        {DirectionType::Follow, "Follow"},
    };

    enum class EntityType {Planet, Star, Station, Asteroid, GasGiant};

    std::map<EntityType, std::string> mapEntityTypeNames {
        {EntityType::Planet, "Planet"},
        {EntityType::Star, "Star"},
        {EntityType::Station, "Station"},
        {EntityType::Asteroid, "Asteroid"},
        {EntityType::GasGiant, "GasGiant"}
    };

    EntityType get_random_entity_type() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, mapEntityTypeNames.size() - 1);

        return static_cast<EntityType>(dis(gen));
    }

    class System {
    private:
        Vector3 position;
        Vector3 size;
        std::string name;
        std::vector<Entity*> entities;
    public:
        System( Vector3 position_, Vector3 size_, std::string name_ )
        : position(position_), size(size_), name(std::move(name_))
        {}
        std::string get_name() { return name; }
        Vector3 get_position() { return position; }
        Vector3 get_size() { return size; }
        void add_entity(Entity* entity) { entities.push_back(entity); }
    };

    class Entity {
    private:
        Vector3 position;
        Vector3 size;
        std::string name;
        Entity* parent = nullptr;
        System* system = nullptr;
        std::vector<Entity*> childrenEntities;
        EntityType type;
        DirectionType directionType;
    public:
        Entity( Vector3 position_, Vector3 size_, std::string name_, System* system_, Entity* parent_ = nullptr,
            EntityType type_ = EntityType::Planet, DirectionType directionType_ = DirectionType::Orbital)
        : position(position_), size(size_), name(std::move(name_)), system(system_), parent(parent_),
        type(type_), directionType(directionType_)
        {}
        void add_child(Entity* child) { childrenEntities.push_back(child); }
        std::string get_name() { return name; }
        std::vector<Entity*> get_children() { return childrenEntities; }
        Vector3 get_position() { return position; }
        Entity get_parent() { return *parent; }
        std::string get_parent_name() const {
            if (parent) return parent->get_name();

            return "null";
        }
        Vector3 get_size() { return size; }
        EntityType get_type() { return type; }
        DirectionType get_direction_type() { return directionType; }
    };
}


int main() {
    constexpr int count_galaxies = 1;
    const Vector3 galaxy_size {1000.0f, 1000.0f, 1000.0f};

    for(int i {0}; i < count_galaxies; i++)
    {
        auto system = MonkeyGalaxy::System(
            Vector3(0.0f, 0.0f, 0.0f),
            galaxy_size,
            "A" + std::to_string(i)
        );

        std::cout << "System: " + system.get_name() + ", generated" << std::endl;
        std::cout << "Generating entities in system: " << std::endl;

        const Vector3 star_size {300.0f, 300.0f, 300.0f};

        auto star = MonkeyGalaxy::Entity(
            Vector3::generate_random_position(galaxy_size),
            star_size,
            system.get_name() + ":S0",
            &system,
            nullptr,
            MonkeyGalaxy::EntityType::Star
        );

        std::cout << "|- Star: " + star.get_name() + ", generated"  << std::endl;
        std::cout << "|   Position: x:" + std::to_string(star.get_position().x) + ", y:" + std::to_string(star.get_position().y) + ", z:" + std::to_string(star.get_position().z) << std::endl;
        std::cout << "|   System: " + system.get_name() << std::endl;
        std::cout << "|   Parent: " + star.get_parent_name() << std::endl;
        std::cout << "|   Type: " + MonkeyGalaxy::mapEntityTypeNames[star.get_type()] << std::endl;
        std::cout << "|   Direction: " + MonkeyGalaxy::mapDirectionTypeNames[star.get_direction_type()] << std::endl;
        std::cout << "|" << std::endl;


        constexpr int count_max_entities = 50;

        for(int e {0}; e < Random::random_int(1, count_max_entities); e++)
        {
            const Vector3 entity_size {100.0f, 100.0f, 100.0f};

            auto entity = MonkeyGalaxy::Entity(
                Vector3::generate_random_position(galaxy_size),
                entity_size,
                system.get_name() + ":E" + std::to_string(e),
                &system,
                &star,
                Random::random_from_enum(std::vector {
                    MonkeyGalaxy::EntityType::Asteroid,
                    MonkeyGalaxy::EntityType::Planet,
                    MonkeyGalaxy::EntityType::GasGiant,
                    MonkeyGalaxy::EntityType::Station
                })
            );

            system.add_entity(&entity);

            std::cout << "|- Entity: " + entity.get_name() + ", generated"  << std::endl;
            std::cout << "|   Position: x:" + std::to_string(entity.get_position().x) + ", y:" + std::to_string(entity.get_position().y) + ", z:" + std::to_string(entity.get_position().z) << std::endl;
            std::cout << "|   System: " + system.get_name() << std::endl;
            std::cout << "|   Parent: " + entity.get_parent_name() << std::endl;
            std::cout << "|   Type: " + MonkeyGalaxy::mapEntityTypeNames[entity.get_type()] << std::endl;
            std::cout << "|   Direction: " + MonkeyGalaxy::mapDirectionTypeNames[entity.get_direction_type()] << std::endl;
            std::cout << "_____" << std::endl;

            if (Random::random_int(0, 2) > 0) {
                constexpr int max_entities_children = 5;
                const Vector3 entity_child_size {10.0f, 10.0f, 10.0f};

                std::cout << "    | #Generating child entity: " << std::endl;
                for(int c {0}; c < Random::random_int(1, max_entities_children); c++)
                {
                    auto entity_child = MonkeyGalaxy::Entity(
                        Vector3::generate_random_position_near(entity.get_position(), entity_size, 50.0f),
                        entity_child_size,
                        entity.get_name() + ":C" + std::to_string(c),
                        &system,
                        &entity,
                        MonkeyGalaxy::get_random_entity_type(),
                        MonkeyGalaxy::DirectionType::Orbital
                    );

                    std::cout << "    |-ChildEntity: " + entity_child.get_name() + ", generated"  << std::endl;
                    std::cout << "    |   Position: x:" + std::to_string(entity_child.get_position().x) + ", y:" + std::to_string(entity_child.get_position().y) + ", z:" + std::to_string(entity_child.get_position().z) << std::endl;
                    std::cout << "    |   Size: x:" + std::to_string(entity_child.get_size().x) + ", y:" + std::to_string(entity_child.get_size().y) + ", z:" + std::to_string(entity_child.get_size().z) << std::endl;
                    std::cout << "    |   System: " + system.get_name() << std::endl;
                    std::cout << "    |   Parent: " + entity_child.get_parent_name() << std::endl;
                    std::cout << "    |   Type: " + MonkeyGalaxy::mapEntityTypeNames[entity_child.get_type()] << std::endl;
                    std::cout << "    |   Direction: " + MonkeyGalaxy::mapDirectionTypeNames[entity_child.get_direction_type()] << std::endl;
                    std::cout << "    |________________________________________   " << std::endl;
                }


            }
        }




    }
}