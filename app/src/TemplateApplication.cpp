#include "TemplateApplication.h"
#include "generated/Classes.generated.h"
#include "generated/Systems.generated.h"

namespace app
{
    TemplateApplication* TemplateApplication::GetTemplateApplication()
    {
        return static_cast<TemplateApplication*>(Get());
    }

    void TemplateApplication::Init()
    {
        Application::Init();
        se::app_InitClassReflection();
        se::app_InitSystems(&m_World);
    }
}
