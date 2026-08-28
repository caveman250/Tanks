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

    class TanksApplication : public se::Application
    {
    public:
        static TanksApplication* GetTemplateApplication();

        void Init() override;
    };
}
