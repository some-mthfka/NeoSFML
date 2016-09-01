#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <InitData.hpp>

#include <SFML/Graphics/Font.hpp>

std::string     toString(const size_t& value);

//the amount of pixels needed to fit a line of text vertically
//given the font and the font size
int             getLineSpacing(const sf::Font &font, int fontSize);
//The amount of pixels needed to fit a char. Monospace is assumed. 
int             getCharWidth(const sf::Font &font, int fontSize);

//Reads data from filename to InitData
InitData        readInitData(std::string filename);

//Given size in rows and columns plus the font and the
//font size, all of which is in InitData, this function
//calculates the size of window that needs to be created
//to hold all the rows and columns.
//The results are kept in initData's videoMode for future 
//use in Application when making a render window.
void            constructVideoMode(InitData &initData);

//Hides console window.
void Stealth();

#endif
