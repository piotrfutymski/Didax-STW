#include "FrameElement.h"

FrameEvent::FrameEvent()
{
}

FrameEvent::FrameEvent(const nlohmann::json& jsn)
{
	name = jsn["name"];
	value = jsn["value"];
}
