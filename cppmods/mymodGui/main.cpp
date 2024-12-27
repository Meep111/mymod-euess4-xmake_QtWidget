#include <string>

#include <Mod/CppUserModBase.hpp>
#include <UE4SSProgram.hpp>
#include "mymodGui.h"
#include <QtWidgets/QApplication>

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    mymodGui w;
//    w.show();
//    return a.exec();
//}
mymodGui* w;
char* argv[] = {(char*)"mymodGui"};
int argc = 1;
QApplication* a;

void psuedoStart()
{
    char* argv[] = {(char*)"mymodGui"};
    int argc = 1;
    a = new QApplication(argc, argv);
    w = new mymodGui();
    w->show();
    a->exec();
}
class mymodUI : public RC::CppUserModBase
{

  public:
    mymodUI() : CppUserModBase()
    {
        ModName = STR("mymodGui");
        ModVersion = STR("1.0");
        ModDescription = STR("testmodUi");
        ModAuthors = STR("truman");

    }

    auto on_unreal_init() -> void override
    {
       
        char* argv[] = {(char*)"mymodGui"};
        int argc = 1;
        a = new QApplication(argc, argv);
        
        w = new mymodGui();
        w->show();
        a->exec();
    }

    auto on_program_start() -> void override
    {
       
        Output::send<LogLevel::Verbose>(STR("mymodGui have started\n"));
    }

    ~mymodUI() override = default;
};

#define MYMOD_MOD_API __declspec(dllexport)
extern "C"
{
    MYMOD_MOD_API RC::CppUserModBase* start_mod()
    {
        return new mymodUI();
    }

    MYMOD_MOD_API void uninstall_mod(RC::CppUserModBase* mod)
    {
        delete mod;
    }
}