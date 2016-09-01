#include <Application.hpp>

#include <sstream>

#include <Utility.hpp>
#include <InitData.hpp>

const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);

Application::Application(const InitData& initData)
    : mInitData(initData)
    , mProgramName("NeoSFML")
    , mResizableWindow(initData.videoMode,
              mProgramName, 
              sf::Style::Close | sf::Style::Resize)
    , mFullscreenWindow(sf::VideoMode::getFullscreenModes()[0],
                        mProgramName,
                        sf::Style::Fullscreen)
    , mCurrentWindow(&mResizableWindow)
    , mStatisticsNumFrames(0)
    , mFullscreen(false)
    , mNeovim(initData, mSignals) 
{
    mFullscreenWindow.setVisible(false);

    if (initData.showFPS)
    {
        mStatisticsText.setFont(mInitData.font);
        mStatisticsText.setColor(sf::Color::Black);
        mStatisticsText.setPosition(0, 0);
        mStatisticsText.setCharacterSize(10u);
    } 
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

    //mWindow.setFramerateLimit(60);

	while (mCurrentWindow -> isOpen())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processInput();
			update(TimePerFrame);
		}

		if (mInitData.showFPS)
            updateStatistics(dt);

		render();
	}
}

void Application::processInput()
{
	sf::Event event;
	while (mCurrentWindow -> pollEvent(event))
	{
        if (event.type == sf::Event::Resized)
        {
            // update the view to the new size of the window
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            mCurrentWindow -> setView(sf::View(visibleArea));
        }

        if (event.type == sf::Event::KeyPressed &&
            event.key.code == sf::Keyboard::F11)
        {
            mFullscreen = !mFullscreen;

            mCurrentWindow -> setVisible(false);

            if (mFullscreen)
                mCurrentWindow = &mFullscreenWindow;
            else
                mCurrentWindow = &mResizableWindow;

            mCurrentWindow -> setVisible(true);

            sf::Event resized;
            resized.type = sf::Event::Resized;
            resized.size.width = mCurrentWindow -> getSize().x;
            resized.size.height = mCurrentWindow -> getSize().y;

            //ultimately adjust nvim's grid size
            //to the new dimensions
            mNeovim.handleEvent(resized);
        }

		mNeovim.handleEvent(event);
	}
}

void Application::update(sf::Time dt)
{
    if (mSignals.setTitle.status)
    {
        mCurrentWindow -> setTitle(mSignals.setTitle.title);
        mSignals.setTitle.status = false;
    }

	mNeovim.update(dt);
}

void Application::render()
{
	mCurrentWindow -> clear();

    mNeovim.render(*mCurrentWindow, sf::RenderStates());

    if (mInitData.showFPS)
        mCurrentWindow -> draw(mStatisticsText);

	mCurrentWindow -> display();
}

void Application::updateStatistics(sf::Time dt)
{
	mStatisticsUpdateTime += dt;
	mStatisticsNumFrames += 1;
	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString("FPS: " + toString(mStatisticsNumFrames));

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}

