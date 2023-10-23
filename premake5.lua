workspace "SparseBitSet"
   configurations { "Debug", "Release" }

project "SparseBitSet"
   kind "ConsoleApp"
   language "C++"
   files {"src/main.cpp"}
   filter { "configurations:Debug" }
      defines { "DEBUG" }
      symbols "On"

   filter { "configurations:Release" }
      defines { "NDEBUG" }
      optimize "On"
