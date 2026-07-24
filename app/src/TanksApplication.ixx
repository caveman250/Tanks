module;

#include "engine/Application.h"

export module TanksApplication;

namespace app
{
    struct Node;
    struct OtherComp;

    export class TanksApplication : public se::Application
    {
    public:
        static TanksApplication* GetTemplateApplication();

        void Init() override;
    };
}
