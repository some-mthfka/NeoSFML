#include <TextureCachingRenderer.hpp>

#include <iostream>

nvim::TextureCachingRenderer::TextureCachingRenderer(const GUIOptions &GUIOptions)
    : mGUIOptions(GUIOptions)
{

}

void nvim::TextureCachingRenderer::resize(sf::Color clearColor)
{
    std::cout << "resizing in texture caching renderer" << std::endl;
    mRenderTexture.create(mGUIOptions.cols() * mGUIOptions.getCharWidth(), 
                          mGUIOptions.rows() * mGUIOptions.getLineSpacing());

    mRenderTexture.clear(clearColor);

    mRenderTextureSprite.setTexture(mRenderTexture.getTexture(), 
                                    /*resetRect =*/ true);
}
