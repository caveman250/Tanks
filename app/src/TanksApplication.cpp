#include "TanksApplication.h"
#include "generated/Classes.generated.h"
#include "generated/Systems.generated.h"
#include "engine/ecs/Prefab.h"

namespace app
{
    TanksApplication* TanksApplication::GetTemplateApplication()
    {
        return static_cast<TanksApplication*>(Get());
    }

    void TanksApplication::Init()
    {
        se::InitClassReflection();
        Application::Init();
        se::app_InitSystems(&m_World);

#if !SPARK_EDITOR
        m_World.LoadScene("/assets/maps/L_Simple.sass");
#endif
    }
}
