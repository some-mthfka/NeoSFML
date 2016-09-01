#ifndef TEXTURE_CACHING_RENDERER_HPP
#define TEXTURE_CACHING_RENDERER_HPP

#include <Nvim/GUIOptions.hpp>

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>

/* Since background renderer and text renderer both
 * keep a render texture to which they draw upon
 * an update and since the code for resizing that render
 * texture is the same (except for clear color) in both
 * cases, it is convenient to have a following class
 * from which the renderers could derive.
 */

namespace nvim
{
    class TextureCachingRenderer
    {
        public:
                 TextureCachingRenderer(const GUIOptions &GUIOptions);

        protected:
            void resize(sf::Color clearColor);

        protected:
            const GUIOptions &
                 mGUIOptions;

            sf::RenderTexture
                 mRenderTexture;

            sf::Sprite 
                 mRenderTextureSprite;
    };
}

#endif
