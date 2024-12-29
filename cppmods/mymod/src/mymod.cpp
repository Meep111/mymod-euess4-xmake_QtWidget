#include "mymod.h"

// Namespace RC::Unreal is used for Unreal Engine classes and functions
using namespace RC::Unreal;

// Global Unreal Engine objects and pointers
Unreal::AActor* myobject;           // Pointer to an actor in the Unreal Engine
Unreal::AActor* myplay;             // Pointer to the player actor
Unreal::UObject* mylevel;           // Pointer to the current level object
FWorldContext* mywolrdcontecx;      // Context object for the current world
Unreal::FFrame* myscriptframePost;  // Pointer to a script execution frame (post callback)
UObject* myscriptframePostContext;  // Context object for the post script frame
Unreal::FFrame* myscriptframePre;   // Pointer to a script execution frame (pre callback)
UObject* myscriptframePreContext;   // Context object for the pre script frame
UPendingNetGame* myupendingnetgameContext; // Context for pending network games
UFunction* postnode;                // Function node for post-callback
UFunction* prenode;                 // Function node for pre-callback
mymodLogger* m_logger;              // Logger instance for logging script activities
UWorld* myworld;                    // Pointer to the Unreal Engine world instance
TArray<FAssetRegistryTag> AssetTags; // Array of asset tags in the current world
AHUD* myhud;                        // Pointer to the HUD (Heads-Up Display) class
sqlite3* db;                        // SQLite database connection object
int rc;                             // SQLite operation result code
char* zErrMsg = 0;                  // SQLite error message buffer

// Namespace alias for the C++17 filesystem library
namespace fs = std::filesystem;

// Constructor for the "mymod" class
dll::mymod::mymod()
{
    // Initialize the mod instance (no additional setup in the constructor)
}

// Called when Unreal Engine has been initialized
void mymod::OnUnrealInitialized()
{
    // Registering various callbacks to hook into Unreal Engine events
    Hook::RegisterBeginPlayPostCallback(&OnActorBeginPlay);
    Hook::RegisterLoadMapPostCallback(&OnMapload);
    Hook::RegisterAActorTickPostCallback(&OnactorTickCb);
    Hook::RegisterProcessLocalScriptFunctionPostCallback(&SciptHookPost);
    Hook::RegisterProcessLocalScriptFunctionPreCallback(&SciptHookPre);
    Hook::RegisterInitGameStatePostCallback(&OnGamestate);
    Hook::RegisterProcessEventPostCallback(&OnEventPost);

    // Logging initialization
    Output::send<LogLevel::Verbose>(STR("mymod has hooked into functions\n"));

    // Open the SQLite database
    OpenDB();

    // Initialize the custom logger
    m_logger = new mymodLogger();
    // m_logger->init("ScriptLog.txt");
}

// Other class lifecycle functions
void mymod::OnProgramStarted() {}
void mymod::OnUpdate() {}

// Callback for when an actor begins play
void mymod::OnActorBeginPlay(Unreal::AActor* Context)
{
    if (Context->GetName().starts_with(STR("BP_Biped_Player_C")))
    {
        myplay = Context; // Assign player context
    }
    else
    {
        myobject = Context; // Assign other actors to a generic object
    }
}

// Callback for actor tick events (post-processing)
void mymod::OnactortickPost(AActorTickCallback callback) {}

// Callback for map loading
std::pair<bool, bool> mymod::OnMapload(UEngine*, FWorldContext& WorldContext, FURL URL, UPendingNetGame* PendingGame, FString& Error)
{
    mywolrdcontecx = &WorldContext;             // Save the world context
    myupendingnetgameContext = PendingGame;     // Save the pending game context
    return std::pair<bool, bool>();             // Default return value
}

// Post script hook callback
void mymod::SciptHookPost(Unreal::UObject* Context, Unreal::FFrame& Stack, void* RESULT_DECL)
{
    myscriptframePost = &Stack;                 // Save the stack frame
    myscriptframePostContext = Context;        // Save the context object
    postnode = Stack.Node();                   // Save the function node

    // Example: Uncomment logging code to track script execution details
    // m_logger->log(Context->GetName().c_str());
}

// Pre script hook callback
void mymod::SciptHookPre(Unreal::UObject* Context, Unreal::FFrame& Stack, void* RESULT_DECL)
{
    myscriptframePre = &Stack;                 // Save the stack frame
    myscriptframePreContext = Context;        // Save the context object
    prenode = Stack.Node();                   // Save the function node
}

// Custom script execution function
void mymod::CallScript(Unreal::UObject* Context, void* RESULT_DECL) {}

// Actor tick callback
void mymod::OnactorTickCb(AActor* Context, float DeltaSeconds) {}

// Callback for game state initialization
void mymod::OnGamestate(AGameModeBase* Context)
{
    mylevel = Context->GetLevel();            // Retrieve the level object
    myworld = Context->GetWorld();           // Retrieve the world object
    myhud = Context->GetHUDClass().Class;    // Retrieve the HUD class
    myworld->UObject::GetAssetRegistryTags(AssetTags); // Retrieve asset tags
}

// Event post-processing callback
void mymod::OnEventPost(UObject* Context, UFunction* Function, void* Parms) {}

// SQLite database callback
int mymod::callback(void* NotUsed, int argc, char** argv, char** azColName)
{
    for (int i = 0; i < argc; i++)
    {
        Output::send<LogLevel::Verbose>(*azColName[i] + STR(" = ") + *argv[i]);
    }
    return 0;
}

// Open the SQLite database
void mymod::OpenDB()
{
    auto asset_path_and_name = Unreal::FName(ensure_str("/Content/SQLiteDB/PhoenixShipData.sqlite"), Unreal::FNAME_Add);

    // Get the asset registry object
    auto* asset_registry = static_cast<Unreal::UAssetRegistry*>(Unreal::UAssetRegistryHelpers::GetAssetRegistry().ObjectPointer);
    if (!asset_registry)
    {
        Output::send<LogLevel::Verbose>(STR("Did not load assets because asset_registry was nullptr\n"));
        return;
    }

    // Load assets and open the SQLite database
    Output::send<LogLevel::Verbose>(STR("Loading assets PhoenixShipData.sqlite\n"));
    Unreal::FAssetData asset_data = asset_registry->GetAssetByObjectPath(asset_path_and_name);
    auto loaded_asset = Unreal::UAssetRegistryHelpers::GetAsset(asset_data);
    auto pathname = m_logger->wcharToString(loaded_asset->GetFullName().c_str());

    rc = sqlite3_open(pathname.c_str(), &db);
    if (!rc)
    {
        Output::send<LogLevel::Verbose>(STR("Can't open database: "));
        sqlite3_close(db);
    }
    else
    {
        Output::send<LogLevel::Verbose>(STR("Opened Database Successfully"));

        // Example SQL commands
        std::string commands1 = "SELECT name FROM sqlite_master WHERE type='table'";
        rc = sqlite3_exec(db, commands1.c_str(), callback, 0, &zErrMsg);
        if (rc != SQLITE_OK)
        {
            Output::send<LogLevel::Verbose>(STR("SQL error:"));
            sqlite3_free(zErrMsg);
        }
    }
    sqlite3_close(db);
}

// Utility function to find a file in a folder
void mymod::findFileInFolder(const std::string& folderPath, const std::string& fileName)
{
    try
    {
        for (const auto& entry : fs::directory_iterator(folderPath))
        {
            if (entry.is_regular_file() && entry.path().filename() == fileName)
            {
                std::cout << "File found: " << entry.path() << '\n';
                return;
            }
        }
        std::cout << "File not found in the folder.\n";
    }
    catch (const fs::filesystem_error& e)
    {
        std::cerr << "Filesystem error: " << e.what() << '\n';
    }
    catch (const std::exception& e)
    {
        std::cerr << "General error: " << e.what() << '\n';
    }
}

// Destructor for the "mymod" class
dll::mymod::~mymod()
{
    // Clean up resources (if necessary)
}
