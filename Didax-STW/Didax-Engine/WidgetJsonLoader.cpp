#include "WidgetJsonLoader.h"
#include "Engine.h"

std::unique_ptr<Didax::Widget> Didax::WidgetJsonLoader::create(const std::string& name, AssetManager* a, Engine* eng, int priority, Entity* e)
{
	auto w = a->getAsset<DataAsset>(name);
	if (w == nullptr)
	{
		Logger::log("Widget with name '" + name + "' is not loaded - check if it defined in JSON file");
		return nullptr;
	}
	auto& widgData = w->data;
	if (!widgData.contains("widgetType"))
	{
		Logger::log("Widget with name '" + name + "' don't have [widgetType] property defined - it's obligatory");
		return nullptr;
	}
	auto res = createFromType(widgData["widgetType"], a, e);
	initWidget(res.get(), widgData, a);
	initExtendedProperties(res.get(), widgData, a);
	if (widgData.contains("children"))
	{
		for (auto& c : widgData["children"])
			addChild(res.get(), c, a, eng, priority + 10);
	}
	return std::move(res);
}

std::unique_ptr<Didax::Widget> Didax::WidgetJsonLoader::createFromType(const std::string& type, AssetManager* a, Entity* e)
{
	if (type == "canvas")
		return std::move(std::make_unique<Didax::Canvas>(a,e));
	else if(type == "textArea")
		return std::move(std::make_unique<Didax::TextArea>(a,e));
	else if(type == "button")
		return std::move(std::make_unique<Didax::Button>(a,e));
	else
	{
		Logger::log("Can't create widget with type: " + type + ", creating canvas instead", Logger::Level::Warn);
		return std::move(std::make_unique<Didax::Canvas>(a,e));
	}
}

void Didax::WidgetJsonLoader::initWidget(Widget* w, nlohmann::json& widgData, AssetManager* a)
{
	if (widgData.contains("rectangle"))
	{
		w->setSize(widgData["rectangle"]["width"], widgData["rectangle"]["height"]);
		w->setPosition(widgData["rectangle"]["x"], widgData["rectangle"]["y"]);
	}
	if (widgData.contains("opacity"))
		w->setColor(sf::Color(255, 255, 255, (widgData["opacity"] * 255) / 100));
	if (widgData.contains("interable"))
		if (!widgData["interable"])
			w->setInterable(false);
}

void Didax::WidgetJsonLoader::initExtendedProperties(Widget* w, nlohmann::json& widgData, AssetManager* a)
{
	if (widgData["widgetType"] == "canvas")
		initCanvas(w, widgData, a);
	else if (widgData["widgetType"] == "button")
		initButton(w, widgData, a);
	else if (widgData["widgetType"] == "textArea")
		initTextArea(w, widgData, a);
}

void Didax::WidgetJsonLoader::initCanvas(Widget* w, nlohmann::json& widgData, AssetManager* a)
{
	auto canv = static_cast<Canvas*>(w);
	if (widgData.contains("background"))
	{
		if (widgData["background"] == "RECTANGLE")
			canv->setRect();
		else
			canv->setTexture(widgData["background"]);
	}
	if (widgData.contains("backgroundColor"))
	{
		int r = widgData["backgroundColor"][0];
		int g = widgData["backgroundColor"][1];
		int b = widgData["backgroundColor"][2];
		canv->setColor(canv->getColor() * sf::Color(r, g, b));
	}
}

void Didax::WidgetJsonLoader::initButton(Widget* w, nlohmann::json& widgData, AssetManager* a)
{
	auto butt = static_cast<Button*>(w);
	if (widgData.contains("background"))
	{
		butt->setTexture(widgData["background"]);
	}
	if (widgData.contains("backgroundColor"))
	{
		int r = widgData["backgroundColor"][0];
		int g = widgData["backgroundColor"][1];
		int b = widgData["backgroundColor"][2];
		butt->setColor(butt->getColor() * sf::Color(r, g, b));
	}
}

void Didax::WidgetJsonLoader::initTextArea(Widget* w, nlohmann::json& widgData, AssetManager* a)
{
	auto txt = static_cast<TextArea*>(w);
	if (widgData.contains("backgroundColor"))
	{
		int r = widgData["backgroundColor"][0];
		int g = widgData["backgroundColor"][1];
		int b = widgData["backgroundColor"][2];
		txt->setBackgroundColor(r, g, b, 255);
	}
	if (widgData.contains("text"))
		txt->setText(DataLoader::sfStringFromJson(widgData["text"]));

	if (widgData.contains("fontcolor"))
	{
		int r = widgData["fontcolor"][0];
		int g = widgData["fontcolor"][0];
		int b = widgData["fontcolor"][0];
		txt->setFontColor(sf::Color(r, g, b));
	}
	if (widgData.contains("fontsize"))
		txt->setCharacterSize(widgData["fontsize"]);

	if (widgData.contains("font"))
		txt->setFont(widgData["font"]);
	else
		txt->setFont(widgData["arial"]);

	if (widgData.contains("margin"))
		txt->setMargin({ widgData["margin"][0], widgData["margin"][1] });
	else
		txt->setMargin({ 5,5 });
	if (widgData.contains("textalign"))
		if (widgData["textalign"] == "center")
			txt->setAlaign(TextArea::Alaign::Center);
		else if(widgData["textalign"] == "left")
			txt->setAlaign(TextArea::Alaign::Left);
		else if (widgData["textalign"] == "right")
			txt->setAlaign(TextArea::Alaign::Right);
}

Didax::Widget* Didax::WidgetJsonLoader::addChild(Widget* parent, std::string name, AssetManager* a, Engine* eng, int priority)
{
	auto ent = eng->addEntity(name);
	auto child = ent->createWidget(name, priority);
	if (child == nullptr)
	{
		Logger::log("Can not create widget with name: " + name);
		return nullptr;
	}
	parent->addChild(child);
	return child;
}
