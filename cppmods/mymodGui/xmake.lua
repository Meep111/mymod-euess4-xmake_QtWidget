-- rule("custom.mod")
    -- add_deps("ue4ss.base", {order = true})
    -- after_load(function(target)
        -- target:set("kind", "shared") --exe or dll
        -- target:set("languages", "cxx20")
        -- target:set("exceptions", "cxx")
        -- target:add("deps", "UE4SS")
        -- target:set("group", "mods")
    -- end)

    -- on_install(function(target)
        -- import("mods.install").install(target)
    -- end)


target("mymodGui")
    add_rules("qt.widgetapp")
	add_rules("ue4ss.mod")
    add_headerfiles("*.h")
    add_files("*.cpp")
    add_files("mymodGui.ui")
    add_files("mymodGui.h")
	
	