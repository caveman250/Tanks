module;
#include "components/PlayerComponent.h"
#include "components/PlayerTurretComponent.h"
#include "editor/util/ViewportUtil.h"
#include "engine/ecs/components/TransformComponent.h"
#include "engine/math/util/ViewportUtil.h"
#include "engine/input/InputComponent.h"
#include "engine/camera/ActiveCameraComponent.h"
#include "engine/ecs/System.h"
#include "engine/ui/Rect.h"
#include "platform/IWindow.h"

export module PlayerTurretSystem;

namespace app
{
    using namespace se;
    export class PlayerTurretSystem : public ecs::AppSystem
    {
        SPARK_SYSTEM()

        static ecs::SystemDeclaration GetSystemDeclaration()
        {
            return ecs::SystemDeclaration()
                .WithComponent<const PlayerTurretComponent>()
                .WithComponent<ecs::components::TransformComponent>()
                .WithSingletonComponent<input::InputComponent>()
                .WithSingletonComponent<camera::ActiveCameraComponent>();
        }

        void OnUpdate(const ecs::QueryResults& results)
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

                math::Vec3 mouseWorldPos = math::util::ScreenToWorldPoint(mousePos
                                                                                , camera->view
                                                                                , camera->proj
                                                                                , math::Vec4(0.f,
                                                                                             0.f,
                                                                                             static_cast<float>(viewportRect.size.x),
                                                                                             static_cast<float>(viewportRect.size.y)),
                                                                                0.f);

                const math::Vec3 direction = math::Normalized(camera->pos - mouseWorldPos);
                mouseWorldPos = direction * camera->pos.y;

                for (size_t i = 0; i < entities.size(); ++i)
                {
                    auto& transform = transforms[i];

                    if (!transform.parent)
                    {
                        continue;
                    }

                    math::Vec3 mouseLocalPos = { mouseWorldPos.z, transform.pos.y, mouseWorldPos.x };
                    math::Mat4 rotMat = math::LookAt(transform.pos, mouseLocalPos, math::Vec3(0.f, 1.f, 0.f));
                    auto inverseTransform = math::Inverse(transform.parent->worldTransform);
                    transform.rot = math::EulerFromMat4(inverseTransform * rotMat);
                }
            });
        }
    };
}
