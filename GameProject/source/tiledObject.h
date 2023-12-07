#pragma once
#include <vector>
#include <string>

namespace tiled {

    class TiledObject {
    public:
        TiledObject() { width = 0; height = 0; x = 0; y = 0; className = ""; }
        virtual ~TiledObject() {}

        int x, y;
        int width;
        int height;
        std::string className;

        // �J�X�^���v���p�e�B
        int arrow;
        int putItem;
    };
}