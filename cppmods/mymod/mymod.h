#pragma once

#include <unordered_map>
#include <unordered_set>

#include <Unreal/FFrame.hpp>
#include <Unreal/UStruct.hpp>
#include<UE4SSProgram.hpp>
#include <Helpers/String.hpp>
#include <ExceptionHandling.hpp>
#include <DynamicOutput/Output.hpp>
#include <DynamicOutput/DynamicOutput.hpp>
#include <Unreal/UObjectGlobals.hpp>
#include <Unreal/UObjectArray.hpp>
#include <Unreal/UFunction.hpp>
#include <Unreal/UPackage.hpp>
#include <Unreal/UObject.hpp>
#include <Unreal/UClass.hpp>
#include <Unreal/AActor.hpp>
#include <Unreal/Hooks.hpp>
#include <AGameModeBase.hpp>
#include <FWorldContext.hpp>
#include <vector>
#include <iostream>
#include <thread>
#include <ranges>
#include <Unreal/FString.hpp>
#include <Unreal/Core/Containers/Array.hpp>
#include <Unreal/ReflectedFunction.hpp>
#include <Unreal/Signatures.hpp>
#include <Unreal/Property/FObjectProperty.hpp>
using namespace RC::Unreal::Hook;

 using namespace RC::Unreal;

    class mymod
    {
      public:
        mymod();

        static void OnUnrealInitialized();
        static void OnProgramStarted();
        static void OnUpdate();
        
        static void OnactortickPost(AActorTickCallback callback);
        static std::pair<bool, bool> OnMapload(UEngine*, FWorldContext& WorldContext, FURL URL, UPendingNetGame* PendingGame, FString& Error);

        static void OnActorBeginPlay(Unreal::AActor* Context);

        static void SciptHookPost(Unreal::UObject* Context, Unreal::FFrame& Stack, void* RESULT_DECL);
        
        static void SciptHookPre(Unreal::UObject* Context, Unreal::FFrame& Stack, void* RESULT_DECL);

        static void OnactorTickCb(AActor* Context, float DeltaSeconds);

        static void OnGMBase(AGameModeBase* Context);
        ~mymod();

      private:

     
    };
