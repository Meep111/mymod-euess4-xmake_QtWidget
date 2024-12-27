local projectName = "mymod"

target(projectName)
    add_rules("ue4ss.mod")
	add_headerfiles("*.h")
    add_files("*.cpp")
	add_files("dllmain.cpp", "mymod.cpp")