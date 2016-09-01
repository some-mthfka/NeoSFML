#include <Nvim/TextRenderer.hpp>

#include <SFML/Graphics/RectangleShape.hpp>

#include <iostream>

nvim::TextRenderer::TextRenderer(nvim::DataHolder &dataHolder, nvim::GUIOptions &GUIOptions)
    : TextureCachingRenderer(GUIOptions)
    , mDataHolder(dataHolder)
    , mGUIOptions(GUIOptions)
{
    setTextOffset(0, 0);

    resize(); //uses mGUIOptions for info
}

void nvim::TextRenderer::update()
{
    sf::RectangleShape cell(sf::Vector2f(mGUIOptions.getCharWidth(), mGUIOptions.getLineSpacing()));
    
    for (int i = 0; i < mGUIOptions.rows(); i++)
    {
        const sf::String &textRow = mDataHolder.getTextAtRow(i);
        const auto &textAttrRow = mDataHolder.getTextAttributesAtRow(i);
        const auto &colorAttrRow = mDataHolder.getColorAttributeAtRow(i);

        auto &rowColors = mDataHolder.getBackgroundColorsAtRow(i);

        for (int j = 0; j < mGUIOptions.cols(); j++) 
        {
            
            if (mTextCache[i][j].getString() != textRow[j] ||
                mTextCache[i][j].getStyle() != textAttrRow[j] ||
                mTextCache[i][j].getColor() != colorAttrRow[j])
                {
                    if (mTextCache.at(i).at(j).getString() != " ")
                    {
                        mTextCache.at(i).at(j).setColor(sf::Color::Transparent);
                        mRenderTexture.draw(mTextCache[i][j], sf::BlendNone);
                    }

                    mTextCache[i][j].setString(textRow[j]);
                    mTextCache[i][j].setStyle(textAttrRow[j]);
                    mTextCache[i][j].setColor(colorAttrRow[j]);

                    mRenderTexture.draw(mTextCache[i][j], sf::BlendNone);
                }
        }
    }

    mRenderTexture.display();
}

void nvim::TextRenderer::resize()
{
    //mTextGrid.resize(mGUIOptions.rows());
    mTextCache.resize(0);

    mTextCache.resize(mGUIOptions.rows());

    for (int i = 0; i < mGUIOptions.rows(); i++)
        mTextCache.at(i).resize(mGUIOptions.cols());

    for (int i = 0; i < mGUIOptions.rows(); i++)
        for (int j = 0; j < mGUIOptions.cols(); j++)
        {
            mTextCache.at(i).at(j).setFont(mGUIOptions.getFont());
            mTextCache.at(i).at(j).setCharacterSize(mGUIOptions.getFontSize());
            //Text, for it to be centered needs to be positioned a bit higher than
            //it would be drawn otherwise. I dunno why. This also eliminates the
            //leftovers from the painted-over removed letters.
            mTextCache.at(i).at(j).setPosition(mGUIOptions.getCharWidth() * j, 
                                               mGUIOptions.getLineSpacing() * i);
            mTextCache.at(i).at(j).setColor(sf::Color::Black);
        }

    mRenderTextureSprite.setPosition(mOffsetX, mOffsetY);

    TextureCachingRenderer::resize(sf::Color::Transparent);

    update();
}

void nvim::TextRenderer::render(sf::RenderTarget &target, const sf::RenderStates &states) const
{
    target.draw(mRenderTextureSprite, states);
}

void nvim::TextRenderer::setTextOffset(int x, int y)
{
    mOffsetX = x;
    mOffsetY = y;
}
