#include "PG/ui/PGUIMessage.h"
#include "PG/ui/PGUIElement.h"

namespace PG {

//--------------------------------------------------------
PGUIMessage PGUIMessage::close(PGUIElement* target_)
{
	return PGUIMessage { kClose, target_, 0 };
}

//--------------------------------------------------------
PGUIMessage PGUIMessage::sendTag(PGTagReciever* target_, int tag_)
{
	return PGUIMessage { kSendTag, target_, tag_ };
}

//--------------------------------------------------------
PGUIMessage PGUIMessage::pushElement(PGUIElement* target_)
{
	return PGUIMessage { kPushElement, target_, 0 };
}

}
