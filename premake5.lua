
-- %{} is a Value Token. Depending on scope they have access to context objects: wks, prj, cfg and file.
-- wks: current workspace
-- prj: project
-- cfg: configurations
-- file: file configuration

workspace "Hazel"      -- For us, this is the name of the Visual Studio solution.
	architecture "x64" -- Platform in Visual Studio
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release", -- Faster version of Debug, but still with Logging. Still for development.
		"Dist"     -- For distribution, no Logging.
	}

-- Lua Variables

-- z.B.:        Debug            windows        x86_64
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Hazel"
	location "Hazel" -- Everything in project Hazel is relative to this path now. location Hazel since this project is inside the Hazel folder in the solution folder.
	kind "SharedLib" -- SharedLib = DLL
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}") -- "a .. b" appends string b to a.
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h", -- ** means recursively search
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src"
	}
	
	filter "system:windows" -- filters make it possible to use certain kinds of configurations only for specific platforms. In this case Windows.
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest" -- Windows SDK Version

		defines
		{
			"HZ_PLATFORM_WINDOWS",
			"HZ_BUILD_DLL"
		}

		postbuildcommands -- Automatic DLL placement after project build
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		symbols "On"

	filter "configurations:Dist" -- Dist := Distribution
		defines "HZ_DIST"
		symbols "On"

project "Sandbox" -- These are all actually function calls, but parantheses can be omitted if only one argument is given
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Hazel/vendor/spdlog/include",
		"Hazel/src"
	}

	links
	{
		"Hazel"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest" 

	defines
	{
		"HZ_PLATFORM_WINDOWS"
	}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "HZ_DIST"
		symbols "On"

project "Test"
	location "Test"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest" 

	filter "configurations:Debug"
		symbols "On"

	filter "configurations:Release"
		symbols "On"