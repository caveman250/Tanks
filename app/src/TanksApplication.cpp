module;
#include "generated/Classes.generated.h"
#include "generated/Systems.generated.h"

module TanksApplication;

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
        se::InitSystems(&m_World);

#if !SPARK_EDITOR
        m_World.LoadScene("/assets/maps/L_Simple.sass");
#endif
    }
}
