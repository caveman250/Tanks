#include <platform/PlatformRunLoop.h>

import Application;

import TanksApplication;

int main(int, char*[])
{
#if SPARK_ENABLE_PROFILING
    EASY_PROFILER_ENABLE;
#endif
    se::Application::CreateInstance<app::TanksApplication>();
    auto runLoop = se::PlatformRunLoop::CreatePlatformRunloop();
    runLoop->Run();
    runLoop->Shutdown();
}
