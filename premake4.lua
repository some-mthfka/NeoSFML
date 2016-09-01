solution "NeoSFML"
    --Uncomment next line to build a debug version.
    --configurations { "Debug" } 
    configurations { "Release", "macosx", "windows", "linux" }
    --For debug, remember to remove -O2 build option.
    --Also uncomment Symbols flag. 

    location("build_"..os.get())
    targetdir("build_"..os.get())

    project "neosfml"
        kind "ConsoleApp"
        language "C++"
        files
        { 
            "src/**.h", 
            "src/**.hpp",
            "src/**.inl",
            "src/**.cpp"
        }

        libdirs {}

        includedirs { "lib/SFML/"..os.get().."/include",
                      "lib/Python33/include", 
                      "src/", 
                      "src/**" }

        libdirs { "lib/SFML/"..os.get().."/lib", "lib/Python33" }
        linkoptions { "-m32" } 
        buildoptions { "-m32", "-O2", "-std=c++11", "-Wall", "-pedantic"} 
        --pedantic-errors flag broke things very badly
        --without giving much (useful) info on why it did so.
        --Changing it for pedantic does not cause a single warning.
                                            --, "-pedantic-errors"
                                            
        configuration "windows"
            includedirs { "D:/Boost/boost_1_60_0" }
            libdirs { "D:/Boost/boost_1_60_0/stage/lib" }
            defines "SFML_STATIC" 
            --flags { "Symbols" } --for Debug
            links
            {
                "sfml-network-s-d",
                "sfml-graphics-s-d",
                "sfml-window-s-d",
                "sfml-system-s-d",
                "opengl32",
                "winmm",
                "gdi32",
                "freetype",
                "jpeg",
                --"ws2_32", --for the network module
                "boost_locale-mgw49-mt-1_60",
                "python33"
            }
            excludes { "src/**/linux/**", "src/**/macosx/**" }

        --WARNING: Not up to date
        configuration "macosx"
            files { "src/**.mm" }
            flags { "Symbols" }
            buildoptions { "-stdlib=libc++" }
            linkoptions { "-stdlib=libc++" }
            links
            {
                "cocoa.framework",
                "ApplicationServices.framework",
                "Foundation.framework",
                "IOKit.framework",

                "sfml-graphics.framework",
                "sfml-window.framework",
                "sfml-system.framework"
            }         

            excludes { "src/**/linux/**", "src/**/windows/**" }

        --WARNING: Not up to date
        configuration "linux"
            flags { "Symbols" }
            linkoptions { "-Wl,-rpath=\\$$ORIGIN/../lib/SFML/linux/lib" }
            links
            {
                "sfml-graphics",
                "sfml-window",
                "sfml-system",
                "X11"
            } 
            excludes { "src/**/macosx/**", "src/**/windows/**" }
