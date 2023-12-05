#include <Entity.hpp>

class EntityFactory {
public:
    static Entity* createStarship() {
        return new Starship();
    }

    static Entity* createBullet() {
        return new Bullet();
    }
};