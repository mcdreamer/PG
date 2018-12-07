#pragma once

#include "PG/ui/UIElement.h"

#include <functional>
#include <vector>
#include <string>

namespace PG {

//--------------------------------------------------------
class Dialog : public UIElement
{
public:
	//-----------------------------------------------------------------
	class Item
	{
	public:
		Item(const std::string& text, const int tag)
		: m_Text(text), m_Tag(tag)
		{}
		
		const std::string&	getText() const { return m_Text; }
		int					getTag() const { return m_Tag; }
		
	private:
		std::string	m_Text;
		int			m_Tag;
	};
	
	using CallbackFunc = std::function<void(int)>;
	
	Dialog(const std::string& message,
		   const std::vector<Item>& items,
		   const CallbackFunc& callback)
	: m_Message(message),
	m_Items(items),
	m_Callback(callback)
	{}
	
private:
	std::string			m_Message;
	std::vector<Item>	m_Items;
	CallbackFunc 		m_Callback;
	
	virtual void initUIElement(const Size& parentSize, const StyleSheet& styleSheet) override final;
	virtual bool receiveTag(const int tag, UIMessageQueuePoster& msgPoster) override;
	virtual	bool isModal() const override final;
};

}
