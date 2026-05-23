#include "TanksApplication.h"
#include "generated/Classes.generated.h"
#include "generated/Systems.generated.h"

namespace app
{
    TanksApplication* TanksApplication::GetTemplateApplication()
    {
        return static_cast<TanksApplication*>(Get());
    }

    void TanksApplication::Init()
    {
        Application::Init();
        se::app_InitClassReflection();
        se::app_InitSystems(&m_World);
    }
}
