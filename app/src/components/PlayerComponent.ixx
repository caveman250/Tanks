module;
#include "engine/ecs/Component.h"

export module PlayerComponent;
namespace app
{
    export struct PlayerComponent : se::ecs::Component
    {
        SPARK_COMPONENT()

        SPARK_MEMBER(Serialized)
        float moveSpeed = 5.f;

        bool isMovingUp = false;
        bool isMovingDown = false;
        bool isMovingLeft = false;
        bool isMovingRight = false;
    };
}
