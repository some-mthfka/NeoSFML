#include <Application.hpp>

#include <stdexcept>
#include <iostream>

#include <InitData.hpp>
#include <Utility.hpp>

/* For overview of this program, see Neovim.hpp */

int main(int argc, char *argv[])
{
    Stealth();

    //file to open as supplied in the argument if any
    std::string filename;

    if (argc > 1)
        filename = std::string(argv[1]);

    //initializing init data
    auto initData = readInitData("neosfml.ini");
    //order matters
    initData.font.loadFromFile(initData.pathToFont);
    initData.fileToOpen = filename;
    constructVideoMode(initData); //called after font is loaded

	try
	{
		Application app(initData);
		app.run();
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
        std::cin.get();
	}
}
