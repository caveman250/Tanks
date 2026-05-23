#pragma once

#include "engine/Application.h"

namespace se::render
{
    class VertexBuffer;
    class Material;
}

namespace app
{
    struct Node;
    struct OtherComp;

    class TemplateApplication : public se::Application
    {
    public:
        static TemplateApplication* GetTemplateApplication();

        void Init() override;
    };
}
