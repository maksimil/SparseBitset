workspace "SparseBitset"
   configurations { "Debug", "Release" }

project "SparseBitset"
   kind "ConsoleApp"
   language "C++"
   files {"src/main.cpp"}
   filter { "configurations:Debug" }
      defines { "DEBUG" }
      symbols "On"

   filter { "configurations:Release" }
      defines { "NDEBUG" }
      optimize "On"
