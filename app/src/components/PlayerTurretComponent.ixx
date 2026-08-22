module;

#include "spark.h"
#include "engine/ecs/Component.h"

export module PlayerTurretComponent;

namespace app
{
    export struct PlayerTurretComponent : se::ecs::Component
    {
        SPARK_COMPONENT()
    };
}
