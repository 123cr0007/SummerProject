#pragma once
#include <vector>
#include "Layer.h"
#include "tiledata.h"
#include "tiledObject.h"

namespace tiled {
    class TiledMap {
    public:
        TiledMap() { width = 0; height = 0; tilewidth = 0; tileheight = 0; }
        virtual ~TiledMap() {}

        int width;
        int height;

        int tilewidth;
        int tileheight;

        std::vector<TiledLayer> layers;
        std::vector<TiledTileset> tilesets;
        std::vector<TiledObject> objects;
    };
}