#pragma once
#include "Widgets.h"

namespace Didax
{
	class Engine;
	class Entity;

class WidgetJsonLoader
{
public:
	static std::unique_ptr<Widget> create(const std::string& name, AssetManager* a, Engine* eng, int priority, Entity* e);

private:
	static std::unique_ptr<Widget> createFromType(const std::string& type, AssetManager* a, Entity* e);

	static void initWidget(Widget* w, nlohmann::json& widgData, AssetManager* a);
	static void initExtendedProperties(Widget* w, nlohmann::json& widgData, AssetManager* a);

	static void initCanvas(Widget* w, nlohmann::json& widgData, AssetManager* a);
	static void initButton(Widget* w, nlohmann::json& widgData, AssetManager* a);
	static void initTextArea(Widget* w, nlohmann::json& widgData, AssetManager* a);

	static Widget* addChild(Widget* parent, std::string name, AssetManager* a, Engine* eng, int priority);

};


}

