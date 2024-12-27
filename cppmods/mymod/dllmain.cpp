#include <string>

#include <GUI/GUITab.hpp>
#include <Mod/CppUserModBase.hpp>
#include <UE4SSProgram.hpp>
#include <mymod.h>

class mymodQt : public RC::CppUserModBase
{

public:
    mymodQt() : CppUserModBase()
    {
        ModName = STR("mymod");
        ModVersion = STR("1.0");
        ModDescription = STR("testmod");
        ModAuthors = STR("truman");

        //register_tab(STR("Kismet Debugger"), [](CppUserModBase* mod) {
        //    UE4SS_ENABLE_IMGUI()
        //    dynamic_cast<KismetDebuggerMod*>(mod)->m_debugger.render();
        //});
    }
    
     auto on_update() -> void override
    {
         mymod::OnUpdate();
    }

    // The 'Unreal' module has been initialized.
    // Before this fires, you cannot use anything in the 'Unreal' namespace.
    auto on_unreal_init() -> void override
    {
        mymod::OnUnrealInitialized();
    }

    auto on_program_start() -> void override
    {
        mymod::OnProgramStarted();
        Output::send<LogLevel::Verbose>(STR("mymod have started\n"));
    }

    ~mymodQt() override = default;
};

#define MYMOD_MOD_API __declspec(dllexport)
extern "C"
{
    MYMOD_MOD_API RC::CppUserModBase* start_mod()
    {
        return new mymodQt();
    }

    MYMOD_MOD_API void uninstall_mod(RC::CppUserModBase* mod)
    {
        delete mod;
    }
}

