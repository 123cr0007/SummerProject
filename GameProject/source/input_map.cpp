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
		std::ifstream file(path + jsonName); // string �� + �ō����o����
		nlohmann::json json;
		file >> json;
		TiledMap* tiledMap = new TiledMap();

		SetTiledLayer(*tiledMap, json.at("layers"));
		SetTiledTileset(*tiledMap, json.at("tilesets"), path);
		return tiledMap;
	}

	void SetTiledLayer(TiledMap& tiledMap, const nlohmann::json layers) {
		// �z��͔͈� For �ŏ����o����
		for(auto& layer : layers)
		{
			if(layer.find("data") != layer.end()) 
			{
				TiledLayer* tiledLayer = new TiledLayer();

				layer.at("width").get_to(tiledLayer->width);
				layer.at("height").get_to(tiledLayer->height);

				nlohmann::json data = layer.at("data");

				// ��{�^�̔z��͒��ڒl�ɂȂ�
				for(auto& value : data) {
					tiledLayer->data.push_back(value);
				}

				tiledMap.layers.push_back(*tiledLayer);

				delete tiledLayer;
			}
			if(layer.find("objects") != layer.end())
			{
				// �I�u�W�F�N�g�z�񂪂��郌�C���[
				nlohmann::json objs = layer.at("objects");
				for(auto& obj : objs) {
					TiledObject* tiledObject = new TiledObject();
					obj.at("x").get_to(tiledObject->x);
					obj.at("y").get_to(tiledObject->y);
					obj.at("width").get_to(tiledObject->width);
					obj.at("height").get_to(tiledObject->height);
					obj.at("class").get_to(tiledObject->className);

					// �J�X�^���v���p�e�B�Ή�
					if(obj.find("properties") != obj.end()) {
						// �J�X�^���v���p�e�B��������
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
		// layer[] ��"objects" �����邩�H
	}

	void SetTiledTileset(TiledMap& tiledMap, const nlohmann::json tilesets, const std::string path) {
		// �z��͔͈� For �ŏ����o����
		for(auto& tileset : tilesets) {
			TiledTileset* tiledTileset = new TiledTileset();

			// tilesets[] �� "source" �����邩�H
			if(tileset.find("source") != tileset.end()) {
				// �^�C���Z�b�g�t�@�C�����ʂɂ���̂ŁA�����ǂݍ���

				tileset.at("source").get_to(tiledTileset->source);

				if(!tiledTileset->source.empty()) {
					// string �� + �ō����o����
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

			// tilesets[] �� "image" �����邩�H
			if(tileset.find("image") != tileset.end()) {
				// �^�C���Z�b�g��񂪊܂܂�Ă���̂ŁA������Z�b�g����
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

