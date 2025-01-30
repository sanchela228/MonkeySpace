#include <array>
#include <iostream>
#include <vector>


// Coordinates calculate MonkeyGalaxy_center -> EntitiesSystem -> EntitiesSystem_center -> Entity -> Entity_center

struct Vector3 {
    float x, y, z;
    Vector3() = default;
    Vector3(float x_, float y_, float z_)
        : x(x_), y(y_), z(z_) {}
};

namespace MonkeyGalaxy {
    class Entity;
    class EntitiesSystem;
    class Grid;

    enum class DirectionType {Orbital, Follow, Idle};
    enum class EntityType {Planet, Star};


    class Grid {
    private:
    };


    class EntitiesSystem {
        Vector3 position;
    private:
        std::string name;
        std::vector<Entity*> entities;
    };

    class Entity {
        Vector3 position;
    private:
        std::string name;
        Entity* parent = nullptr;
        std::vector<Entity*> childrenEntities;
        EntityType type;
        DirectionType directionType;
    public:
    };
}







// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    // TIP Press <shortcut actionId="RenameElement"/> when your caret is at the
    // <b>lang</b> variable name to see how CLion can help you rename it.
    const auto lang = "C++";

    std::cout << "Hello and welcome to " << lang << "!\n";


    for (int i = 1; i <= 5; i++) {
        // TIP Press <shortcut actionId="Debug"/> to start debugging your code.
        // We have set one <icon src="AllIcons.Debugger.Db_set_breakpoint"/>
        // breakpoint for you, but you can always add more by pressing
        // <shortcut actionId="ToggleLineBreakpoint"/>.
        std::cout << "i = " << i << std::endl;
    }

    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.