#include <mymod.h>


 using namespace RC::Unreal;

 Unreal::AActor* myobject;
 Unreal::AActor* myplay;
 Unreal::UObject* mylevel;
 FWorldContext* mywolrdcontecx;
 Unreal::FFrame* myscriptframePost;
 UObject* myscriptframePostContext;
 Unreal::FFrame* myscriptframePre; 
 UObject* myscriptframePreContext;
 UPendingNetGame* myupendingnetgameContext;
 UFunction* postnode;
 UFunction* prenode;

    mymod::mymod()
    {
        
    }

    void mymod::OnUnrealInitialized()
    {
        Hook::RegisterBeginPlayPostCallback(&OnActorBeginPlay);
        Hook::RegisterLoadMapPostCallback(&OnMapload);
        Hook::RegisterAActorTickPostCallback(&OnactorTickCb);
        Hook::RegisterProcessLocalScriptFunctionPostCallback(&SciptHookPost);
        Hook::RegisterProcessLocalScriptFunctionPreCallback(&SciptHookPre);
        Hook::RegisterInitGameStatePostCallback(&OnGMBase);
        Output::send<LogLevel::Verbose>(STR("mymod have Hooked into functions\n"));
    }

    void mymod::OnProgramStarted()
    {
    }

    void mymod::OnUpdate()
    {
    }

    void mymod::OnActorBeginPlay(Unreal::AActor* Context)
    {
      
        if (Context->GetName().starts_with(STR("BP_Biped_Player_C")))
        {
            myplay = Context;
            
        }
        else
        {
            myobject = Context;
        }
    }

    void mymod::OnactortickPost(AActorTickCallback callback)
    {

    }

    std::pair<bool, bool> mymod::OnMapload(UEngine*, FWorldContext& WorldContext, FURL URL, UPendingNetGame* PendingGame, FString& Error)
    {
        return std::pair<bool, bool>();
        mywolrdcontecx = &WorldContext;
        myupendingnetgameContext = PendingGame;
        
    }

    void mymod::SciptHookPost(Unreal::UObject* Context, Unreal::FFrame& Stack, void* RESULT_DECL)
    {
        myscriptframePost = &Stack;
        myscriptframePostContext = Context;
        postnode = Stack.Node();
      
    }
  
    void mymod::SciptHookPre(Unreal::UObject* Context, Unreal::FFrame& Stack, void* RESULT_DECL)
    {
        myscriptframePre = &Stack;
        myscriptframePreContext = Context;
        prenode = Stack.Node();
    }

    void mymod::OnactorTickCb(AActor* Context, float DeltaSeconds)
    {
    }

    void mymod::OnGMBase(AGameModeBase* Context)
    {
        mylevel=Context->GetLevel();
    }

    mymod::~mymod()
    {

    }
