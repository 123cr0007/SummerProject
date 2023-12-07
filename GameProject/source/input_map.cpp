#include "DxLib.h"
#include "nlohmann/json.hpp"
#include <string>
#include <fstream>
#include "mapdata.h"
#include "tiledata.h"
#include "map.h"

namespace tiled {

	void SetTiledLayer(TiledMap& tiledMap, const nlohmann::json layers);
	void SetTiledTileset(TiledMap& tiledMap, const nlohmann::json tilesets, const std::string path);

	TiledMap* In(const std::string path, const std::string jsonName)
	{
		std::ifstream file(path + jsonName); // string は + で合成出来る
		nlohmann::json json;
		file >> json;
		TiledMap* tiledMap = new TiledMap();

		SetTiledLayer(*tiledMap, json.at("layers"));
		SetTiledTileset(*tiledMap, json.at("tilesets"), path);
		return tiledMap;
	}

	void SetTiledLayer(TiledMap& tiledMap, const nlohmann::json layers) {
		// 配列は範囲 For で処理出来る
		for(auto& layer : layers)
		{
			if(layer.find("data") != layer.end()) 
			{
				TiledLayer* tiledLayer = new TiledLayer();

				layer.at("width").get_to(tiledLayer->width);
				layer.at("height").get_to(tiledLayer->height);

				nlohmann::json data = layer.at("data");

				// 基本型の配列は直接値になる
				for(auto& value : data) {
					tiledLayer->data.push_back(value);
				}

				tiledMap.layers.push_back(*tiledLayer);

				delete tiledLayer;
			}
			if(layer.find("objects") != layer.end())
			{
				// オブジェクト配列があるレイヤー
				nlohmann::json objs = layer.at("objects");
				for(auto& obj : objs) {
					TiledObject* tiledObject = new TiledObject();
					obj.at("x").get_to(tiledObject->x);
					obj.at("y").get_to(tiledObject->y);
					obj.at("width").get_to(tiledObject->width);
					obj.at("height").get_to(tiledObject->height);
					obj.at("class").get_to(tiledObject->className);

					// カスタムプロパティ対応
					if(obj.find("properties") != obj.end()) {
						// カスタムプロパティがあった
						nlohmann::json properties = obj.at("properties");
						for(auto& property : properties) {
							std::string name;
							property.at("name").get_to(name);

							if(name == "arrow") {
								property.at("value").get_to(tiledObject->arrow);
							}
							if (name == "putItem") {
								property.at("value").get_to(tiledObject->putItem);
							}
						}
					}

					tiledMap.objects.push_back(*tiledObject);
					delete tiledObject;
				}
			}
		}
		// layer[] に"objects" があるか？
	}

	void SetTiledTileset(TiledMap& tiledMap, const nlohmann::json tilesets, const std::string path) {
		// 配列は範囲 For で処理出来る
		for(auto& tileset : tilesets) {
			TiledTileset* tiledTileset = new TiledTileset();

			// tilesets[] に "source" があるか？
			if(tileset.find("source") != tileset.end()) {
				// タイルセットファイルが別にあるので、それを読み込む

				tileset.at("source").get_to(tiledTileset->source);

				if(!tiledTileset->source.empty()) {
					// string は + で合成出来る
					std::ifstream tilesetFile(path + tiledTileset->source);
					nlohmann::json tilesetJson;
					tilesetFile >> tilesetJson;

					tilesetJson.at("image").get_to(tiledTileset->image);
					tilesetJson.at("imagewidth").get_to(tiledTileset->imagewidth);
					tilesetJson.at("imageheight").get_to(tiledTileset->imageheight);
					tilesetJson.at("tilewidth").get_to(tiledTileset->tilewidth);
					tilesetJson.at("tileheight").get_to(tiledTileset->tileheight);
					tilesetJson.at("tilecount").get_to(tiledTileset->tilecount);
					tilesetJson.at("columns").get_to(tiledTileset->columns);
				}
			}

			// tilesets[] に "image" があるか？
			if(tileset.find("image") != tileset.end()) {
				// タイルセット情報が含まれているので、それをセットする
				tileset.at("image").get_to(tiledTileset->image);
				tileset.at("imagewidth").get_to(tiledTileset->imagewidth);
				tileset.at("imageheight").get_to(tiledTileset->imageheight);
				tileset.at("tilewidth").get_to(tiledTileset->tilewidth);
				tileset.at("tileheight").get_to(tiledTileset->tileheight);
				tileset.at("tilecount").get_to(tiledTileset->tilecount);
				tileset.at("columns").get_to(tiledTileset->columns);
			}

			tiledMap.tilesets.push_back(*tiledTileset);

			delete tiledTileset;
		}
	}
}

