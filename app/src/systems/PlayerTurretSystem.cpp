#include "PlayerTurretSystem.h"

#include "components/PlayerTurretComponent.h"
#include "engine/ecs/components/TransformComponent.h"
#include "engine/input/InputComponent.h"
#include "engine/camera/ActiveCameraComponent.h"
#include "engine/math/util/ViewportUtil.h"
#include "engine/input/InputUtil.h"
#include "engine/ui/Rect.h"
#include "components/BulletComponent.h"
#include "components/HealthComponent.h"
#include "engine/ecs/Signal.h"
#include "engine/geo/components/AABBColliderComponent.h"
#include "engine/geo/singleton_components/CollisionComponent.h"
#include "engine/geo/util/CollisionUtil.h"
#include "platform/IWindow.h"

namespace app
{
    ecs::SystemDeclaration PlayerTurretSystem::GetSystemDeclaration()
    {
        return ecs::SystemDeclaration()
               .WithComponent<const PlayerTurretComponent>()
               .WithComponent<ecs::components::TransformComponent>()
               .WithSingletonComponent<input::InputComponent>()
               .WithSingletonComponent<camera::ActiveCameraComponent>();
    }

    void PlayerTurretSystem::OnUpdate(const ecs::QueryResults& results)
    {
        ecs::ForEachArcheType(results, ecs::UpdateMode::SingleThreaded, false, [](const ecs::SystemUpdateData& updateData)
        {
            const auto& entities = updateData.GetEntities();
            auto* transforms = updateData.GetComponentArray<ecs::components::TransformComponent>();
            auto* input = updateData.GetSingletonComponent<input::InputComponent>();
            auto* camera = updateData.GetSingletonComponent<camera::ActiveCameraComponent>();

#if SPARK_EDITOR
            const auto viewportRect = Application::Get()->GetEditor()->GetViewportRect();
            const math::IntVec2 mousePos = editor::util::ScreenSpaceToGameViewportSpace( input->mouseX,  input->mouseY);
#else
            auto* window = Application::Get()->GetWindow();
            const auto viewportRect = ui::Rect{ { 0, 0 },  { window->GetWidth(), window->GetHeight()} };
            const math::IntVec2 mousePos = { input->mouseX, input->mouseY };
#endif

            for (size_t i = 0; i < entities.size(); ++i)
            {
                const auto& entity = entities[i];
                auto& transform = transforms[i];

                if (transform.parent)
                {
                    math::Vec3 worldPos = math::Vec3{ transform.worldTransform[3].x, transform.worldTransform[3].y, transform.worldTransform[3].z };
                    if (worldPos == std::numeric_limits<float>::max())
                    {
                        continue;
                    }

                    math::Vec3 mouseWorldPos = math::util::ScreenToWorldPoint(mousePos
                                                          , camera->pos
                                                          , camera->view
                                                          , camera->proj
                                                          , math::Vec4(0.f,
                                                              0.f,
                                                              static_cast<float>(viewportRect.size.x),
                                                              static_cast<float>(viewportRect.size.y)),
                                                          worldPos.y);

                    math::Vec3 mouseLocalPos = math::Inverse(transform.parent->worldTransform) * math::Vec4{ mouseWorldPos.x, mouseWorldPos.y, mouseWorldPos.z, 1.f };

                    const math::Vec3 f(math::Normalized(mouseLocalPos - transform.pos));
                    const math::Vec3 s(math::Normalized(Cross(f, math::Vec3(0.f, 1.f, 0.f))));
                    const math::Vec3 u(Cross(s, f));

                    math::Mat4 rotMat(1);
                    rotMat[0][0] = s.x;
                    rotMat[1][0] = s.y;
                    rotMat[2][0] = s.z;
                    rotMat[0][1] = u.x;
                    rotMat[1][1] = u.y;
                    rotMat[2][1] = u.z;
                    rotMat[0][2] = f.x;
                    rotMat[1][2] = f.y;
                    rotMat[2][2] = f.z;
                    rotMat[3][0] = -Dot(s, transform.pos);
                    rotMat[3][1] = -Dot(u, transform.pos);
                    rotMat[3][2] = Dot(f, transform.pos);
                    transform.rot = math::EulerFromMat4(rotMat);

                    worldPos = math::Vec3{ transform.worldTransform[3].x, transform.worldTransform[3].y, transform.worldTransform[3].z };
                    input::InputUtil::ProcessMouseEvents(entity, input, [transform, worldPos, entity, f](const input::MouseEvent& mouseEvent)
                    {
                        if (mouseEvent.button == input::MouseButton::Left && mouseEvent.state == input::KeyState::Down)
                        {
                            auto* world = Application::Get()->GetWorld();
                            math::Vec3 forward = transform.parent->worldTransform * math::Vec4(f, 0.f);
                            auto bulletPos = worldPos + forward * 2;

                            auto newPrefab = world->InstantiatePrefab(world->GetDefaultScene(), asset::AssetManager::Get()->GetAsset<ecs::Prefab>("/assets/prefabs/bullet.sass"), &bulletPos, nullptr, nullptr, false);
                            std::function func = [forward, parent = entity](const ecs::Id&, BulletComponent* bullet, geo::components::AABBColliderComponent* aabb)
                            {
                                bullet->velocity = forward;

                                aabb->onCollisionEnter.Subscribe([](ecs::Id bullet, ecs::Id other)
                                {
                                    auto* world = Application::Get()->GetWorld();
                                    world->DestroyEntity(bullet);
                                    if (world->HasComponent<HealthComponent>(other))
                                    {
                                        auto* health = world->GetComponent<HealthComponent>(other);
                                        health->health -= 20;
                                    }
                                });

                            };
                            newPrefab.ForEachEntity<BulletComponent, geo::components::AABBColliderComponent>(func);
                        }

                        return false;
                    });
                }

            }
        });
    }
}
