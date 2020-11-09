outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
print("bruh")
workspace "GamejamFramework"
    language "C++"
    cppdialect "C++17"
    architecture "x86_64"
    staticruntime "Off"
    systemversion "latest"
    configurations {
        "Debug", 
        "Release"
    }

    filter {"system:windows"}
        defines {
            "_CRT_SECURE_NO_WARNINGS",
            "NOMINMAX"
        }


    project "Framework"
        location "Framework"
        kind "StaticLib"


        files {
            "%{prj.name}/src/**.cpp",
            "%{prj.name}/src/**.c",
            "%{prj.name}/include/**.h",
            "%{prj.name}/include/**.hpp",
            "%{prj.name}/src/**.hpp"
        }

        includedirs {
            "%{prj.location}/include",
            "%{prj.location}/src"
        }

        libdirs
        {
            "%{prj.name}/lib/x64"
        }

        links {
            "SDL2",
            "SDL2_image",
            "SDL2_mixer"
        }

        debugenvs 
        {
            "PATH=%PATH%;$(ProjectDir)/x64"
        }

        
        warnings "Extra"

        targetdir ("%{prj.name}/bin/" .. outputDir .. "/%{prj.name}")
        objdir ("%{prj.name}/bin-int/" .. outputDir .. "/%{prj.name}")

        filter {"configurations:Debug"}
            symbols "On"
            defines {
                "DEBUG"
            }

        filter {"configurations:Release"}
            optimize "On"
            defines {
                "NDEBUG"
            }


        
    project "Sandbox"
        location "Sandbox"
        kind "ConsoleApp"

        targetdir ("%{prj.name}/bin/" .. outputDir .. "/%{prj.name}")
        objdir ("%{prj.name}/bin-int/" .. outputDir .. "/%{prj.name}")

        files {
            "%{prj.name}/src/**.cpp",
            "%{prj.name}/include/**.h",
            "%{prj.name}/include/**.hpp"
        }

       -- libdirs
        --{
       --     "../Framework/bin/Debug-windows-x86_64/Framework"
        --}

        links {
            "Framework"
        }

        includedirs {
            "%{prj.name}/include",
            "Framework/include"
        }

        debugenvs 
        {
            "PATH=%PATH%;$(ProjectDir)/../Framework/x64"
        }

        filter {"configurations:Debug"}
            symbols "On"
            defines {
                "DEBUG"
            }

        filter {"configurations:Release"}
            optimize "On"
            defines {
                "NDEBUG"
            }
