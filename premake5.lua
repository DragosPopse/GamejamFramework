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
        
        warnings "Extra"

        targetdir ("%{prj.name}/bin/" .. outputDir .. "/Gamejam")
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

        links {
            "Gamejam"
        }

        includedirs {
            "%{prj.name}/include",
            "Framework/include"
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
