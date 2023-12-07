#pragma once
#include <string>

namespace tiled {

    class TiledTileset {
    public:
        TiledTileset() { imagewidth = 0; imageheight = 0; tilewidth = 0; tileheight = 0; tilecount = 0; columns = 0; }
        virtual ~TiledTileset() {}

        std::string source;

        std::string image;
        int imagewidth;
        int imageheight;

        int tilewidth;
        int tileheight;

        int tilecount;
        int columns;
    };
}
