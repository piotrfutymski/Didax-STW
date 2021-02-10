#pragma once
#include <string>
#include "Didax-Engine/Engine.h"

class FrameEvent
{
public:

	FrameEvent();

	FrameEvent(const nlohmann::json& jsn);

	std::string name;
	std::string value;
	Didax::Entity_ptr caller;


};

