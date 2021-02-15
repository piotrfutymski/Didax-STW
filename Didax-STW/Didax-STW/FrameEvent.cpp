#include "FrameElement.h"

FrameEvent::FrameEvent()
{
}

FrameEvent::FrameEvent(const std::string& n, const std::string& v)
{
	name = n;
	value = v;
}

FrameEvent::FrameEvent(const nlohmann::json& jsn)
{
	name = jsn["name"];
	value = jsn["value"];
}
