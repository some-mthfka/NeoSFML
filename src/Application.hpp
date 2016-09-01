#ifndef APPLICATION_HPP
#define APPLICATION_HPP

//Application.hpp and Application.cpp were taken as examples from
//https://github.com/SFML/SFML-Game-Development-Book
//and are modified. The license applies. Please refer
//the to URL above for details.

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include <Nvim/Neovim.hpp>

#include <Signals.hpp>

class Application
{
	public:
		     Application(const InitData &initData);
		void run();

	private:
		void processInput();
		void update(sf::Time dt);
		void render();

		void updateStatistics(sf::Time dt);

	private:
		static const sf::Time	
             TimePerFrame;

        const InitData         
            &mInitData;

        Signals                 
             mSignals;

        std::string             
             mProgramName;

		sf::RenderWindow		
             mResizableWindow, 
             mFullscreenWindow,
            *mCurrentWindow;

		sf::Text 
             mStatisticsText;

		sf::Time 
             mStatisticsUpdateTime;

		std::size_t 
             mStatisticsNumFrames;

        bool mFullscreen;

        nvim::Neovim 
             mNeovim;
};

#endif // APPLICATION_HPP
