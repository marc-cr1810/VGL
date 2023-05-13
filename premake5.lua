include "./external/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

workspace "VGL"
	architecture "x86_64"
	startproject "VGL"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "external/GLFW"
group ""

group "Core"
	include "premake5_vgl.lua"
group ""
