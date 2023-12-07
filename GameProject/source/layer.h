#pragma once
#include <vector>
namespace tiled {
    class TiledLayer {
    public:
        TiledLayer() { width = 0; height = 0; HP = 0; }
        virtual ~TiledLayer() {}

        int width;
        int height;
        int HP;

        std::vector<unsigned int> data;
    };
}