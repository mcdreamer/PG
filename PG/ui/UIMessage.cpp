#include "PG/ui/UIMessage.h"
#include "PG/ui/UIElement.h"

namespace PG {

//--------------------------------------------------------
UIMessage UIMessage::close(UIElement* target_)
{
	return UIMessage { kClose, target_, 0 };
}

//--------------------------------------------------------
UIMessage UIMessage::sendTag(TagReciever* target_, int tag_)
{
	return UIMessage { kSendTag, target_, tag_ };
}

//--------------------------------------------------------
UIMessage UIMessage::pushElement(UIElement* target_)
{
	return UIMessage { kPushElement, target_, 0 };
}

}
