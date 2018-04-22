-- https://github.com/premake/premake-core/wiki

local action = _ACTION or ""

local VULKAN_SDK = os.getenv("VULKAN_SDK");

solution "cinder-vulkan"
    location (action)
    configurations { "Debug", "Release" }
    language "C++"

    configuration "vs*"

        platforms {"x64", "x86"}
        cppdialect "C++11"

        defines {
            "_CRT_SECURE_NO_WARNINGS",
            "_CRT_SECURE_NO_DEPRECATE",
            "NOMINMAX",
        }

        disablewarnings {
            "4244",
            "4305",
            "4996",
        }

        flags {
            "StaticRuntime",
        }

        configuration "x86"
            targetdir ("lib/msw/x86")

        configuration "x64"
            targetdir ("lib/msw/x64")

    -- configuration "vs*uwp"

    --     platforms {"x64", "x86"}

    --     defines {
    --         "_CRT_SECURE_NO_WARNINGS",
    --         "_CRT_SECURE_NO_DEPRECATE",
    --     }

    --     disablewarnings {
    --         "4244",
    --         "4305",
    --         "4996",
    --     }

    --     flags {
    --         "StaticRuntime",
    --     }

    --     configuration "x86"
    --         targetdir ("lib/msw_uwp/x86")

    --     configuration "x64"
    --         targetdir ("lib/msw_uwp/x64")

    configuration "macosx"
        cppdialect "gnu++11"
        platforms {"x64"}
        targetdir ("lib/macos")

    flags {
        "MultiProcessorCompile",
    }

    configuration "Debug"
        defines { "DEBUG" }
        symbols "On"
        targetsuffix "-d"

    configuration "Release"
        defines { "NDEBUG" }
        optimize "On"

    project "cinder-vulkan"
        kind "StaticLib"

        defines {
            "AMD_EXTENSIONS",
            "NV_EXTENSIONS",
        }

        includedirs {
            "include",
            path.join(VULKAN_SDK, "include"),
            path.join(VULKAN_SDK, "glslang"),
            "../../include",
        }
        
        sysincludedirs {
            "include",
            path.join(VULKAN_SDK, "include"),
            "../../include",
        }
        
        files {
            "include/**",
            "src/**",
            path.join(VULKAN_SDK, "glslang", "SPIRV/**"),
            path.join(VULKAN_SDK, "glslang", "OGLCompilersDLL/**"),
            path.join(VULKAN_SDK, "glslang/glslang", "public/**"),
            path.join(VULKAN_SDK, "glslang/glslang", "GenericCodeGen/**"),
            path.join(VULKAN_SDK, "glslang/glslang", "MachineIndependent/**"),
            path.join(VULKAN_SDK, "glslang/glslang", "OSDependent/Windows/ossource.cpp"),
        }
