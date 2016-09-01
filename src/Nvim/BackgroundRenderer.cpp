#include <Nvim/BackgroundRenderer.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Clock.hpp>

nvim::BackgroundRenderer::BackgroundRenderer(nvim::DataHolder &dataHolder, nvim::GUIOptions &GUIOptions)
    : TextureCachingRenderer(GUIOptions)
    , mDataHolder(dataHolder)
    , mGUIOptions(GUIOptions)
{   
    resize(); //takes size info from mGUIOptions
}

void nvim::BackgroundRenderer::update()
{
    sf::RectangleShape cell(sf::Vector2f(mGUIOptions.getCharWidth(), mGUIOptions.getLineSpacing()));

    for (int i = 0; i < mGUIOptions.rows(); i++)
    {
        auto &rowColors = mDataHolder.getBackgroundColorsAtRow(i);

        for (int j = 0; j < mGUIOptions.cols(); j++)
        {
            if (mBackgroundColorCache.at(i).at(j) != rowColors[j])
            {
                cell.setPosition(mGUIOptions.getCharWidth() * j, 
                                 mGUIOptions.getLineSpacing() * i);
                cell.setFillColor(rowColors[j]);

                mRenderTexture.draw(cell, sf::BlendNone);

                mBackgroundColorCache[i][j] = rowColors[j];
            }
        }
    }

    mRenderTexture.display();
}

void nvim::BackgroundRenderer::resize()
{
    mBackgroundColorCache.resize(0);
    std::vector<sf::Color> colorRow;
    colorRow.resize(mGUIOptions.cols(), sf::Color::White);
    mBackgroundColorCache.resize(mGUIOptions.rows(), colorRow);

    TextureCachingRenderer::resize(sf::Color::White);

    update();
}

void nvim::BackgroundRenderer::render(sf::RenderTarget &target, const sf::RenderStates &states) const
{
    target.draw(mRenderTextureSprite, states);
}
