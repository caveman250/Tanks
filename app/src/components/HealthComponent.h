#pragma once
#include "engine/ecs/Component.h"
#include "engine/math/math.h"

namespace app
{
    struct HealthComponent : se::ecs::Component
    {
        SPARK_COMPONENT()

        SPARK_MEMBER(Serialized)
        float health = 100;
    };
}
