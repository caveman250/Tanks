#pragma once
#include "engine/ecs/Component.h"
#include "engine/math/math.h"

namespace app
{
    struct BulletComponent : se::ecs::Component
    {
        SPARK_COMPONENT()

        SPARK_MEMBER(Serialized)
        se::math::Vec3 velocity = {};
    };
}
