#include <Utility.hpp>

#include <iostream>
#include <sstream>
#include <fstream>

#include <tuple>

std::string toString(const size_t& value)
{
    std::stringstream stream;
    stream << value;
    return stream.str();
}

int getLineSpacing(const sf::Font &font, int fontSize)
{
    return font.getLineSpacing(fontSize);
}

int getCharWidth(const sf::Font &font, int fontSize)
{
    return font.getGlyph('A', fontSize, false).advance;
}

void constructVideoMode(InitData &initData)
{
    initData.videoMode.width  = initData.cols * getCharWidth(initData.font, 
                                                             initData.fontSize); 
    initData.videoMode.height = initData.rows * getLineSpacing(initData.font,
                                                               initData.fontSize);

    //in case the requested rows or cols cannot fit into the screen
    if (initData.videoMode.width > sf::VideoMode::getDesktopMode().width)
    {
        initData.videoMode.width = sf::VideoMode::getDesktopMode().width;
        initData.cols = initData.videoMode.width /
                        getCharWidth(initData.font, initData.fontSize);
    }

    if (initData.videoMode.height > sf::VideoMode::getDesktopMode().height)
    {
        initData.videoMode.height = sf::VideoMode::getDesktopMode().height;
        initData.rows = initData.videoMode.height /
                        getLineSpacing(initData.font, initData.fontSize);
    }
}

void generateIniFile(std::string filename)
{
    std::ofstream out(filename);

    out <<
        "-- Comments start with two dashes.\n"
        "-- Comments and blank lines are ignored.\n"
        "-- The order of values matters.\n"
        "-- Feel free to remove this file in case something goes wrong. \n"
        "-- It will be regenerated on the first launch of the program.\n"
        "\n"
        "-- Absolute path to a font to be used\n"
        "media/monospace.ttf\n"
        "\n"
        "-- Font size\n"
        "20\n"
        "\n"
        "-- Size: default # of rows\n"
        "24\n"
        "\n"
        "-- Size: default # of columns\n"
        "80\n"
        "\n"
        "-- Text offset: two integer value in pixels, negatives are allowed.\n"
        "-- For some reason text does not align well with the actual grid\n"
        "-- but shifting it a few pixels makes it tick.\n"
        "--\n"
        "-- Horizontal offset\n"
        "0\n"
        "-- Vertical offset\n"
        "-2\n"
        "\n"
        "-- Show frames per second(true for show, false for not show)\n"
        "false";
}

InitData readInitData(std::string filename)
{
    InitData initData;

    std::ifstream in(filename);

    if (!in.is_open())
    {
        generateIniFile(filename);

        in.open(filename);
    }

    if (!in.is_open())
    {
        std::cerr << "Failed to load and then to generate ini file" << std::endl;
        exit(true);
    }
    else
    {
        const int size = 256;
        char buffer[size];

        std::stringstream str;

        while (in.getline(buffer, size))
            if (buffer[0] != '\0' && (buffer[0] != '-' || buffer[1] != '-')) //not comment or empty line
                str << buffer << '\n';

        str >> std::boolalpha
            >> initData.pathToFont
            >> initData.fontSize
            >> initData.rows 
            >> initData.cols
            >> initData.xTextOffset
            >> initData.yTextOffset
            >> initData.showFPS;

        /*
        std::cout
             << std::boolalpha 
             << initData.pathToFont << std::endl
             << initData.fontSize << std::endl
             << initData.rows  << std::endl
             << initData.cols << std::endl
             << initData.xTextOffset << std::endl
             << initData.yTextOffset << std::endl
             << initData.allowWindowToNeovimGridAdjustment << std::endl
             << initData.showFPS << std::endl;
             */
                
    }

    return initData;
}

#ifdef _WIN32
#include <windows.h>
//Used to hide console window.
//Compiling as WindowedApp did not work out - program just did not work.
//FreeConsole has the same effect as WindowedApp.
//Thanks to the udit043 from stackoverflow, console can be hidden.
//http://stackoverflow.com/questions/622592/win32-programming-hiding-console-window
void Stealth()
{
    HWND Stealth;
    AllocConsole();
    Stealth = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(Stealth,0);
}
#else
void Stealth()
{
    std::cout << "Stealth(): Hiding console is not implemented on this platform." << std::endl;
}
#endif
