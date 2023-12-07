#pragma once
#include <string>
#include "Map.h"

namespace tiled {
    TiledMap* In(const std::string path, const std::string jsonName);
}