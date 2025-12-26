#pragma once

#include <SFML/Graphics.hpp>
#include "../core/Config.h"

/**
 * @todo This class is very early state. todos:
 * - Add user map & car selection system
 * - Add user map & car selection ui
 * - Add if no asset create basic shape instead of assets
 * @brief Resource class that is resources assets
 */
namespace Resource
{
    inline sf::Font Font;
    inline sf::Texture CarTexture;
    inline sf::Texture BackgroundTexture;

    inline bool loadFonts()
    {
        return Font.loadFromFile(Config::FontPath);
    }

    inline bool loadBackGrounds()
    {
        return CarTexture.loadFromFile(Config::CarAssetPath);
    }

    inline bool loadCarAssets()
    {
        return BackgroundTexture.loadFromFile(Config::BackGroundPath);
    }
}