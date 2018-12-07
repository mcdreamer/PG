#include "PG/ui/Bar.h"
#include "PG/core/MathsUtils.h"
#include "PG/graphics/NodeCreator.h"

namespace PG {

//--------------------------------------------------------
Bar::Bar(const Point& position,
		 const Size& size,
		 const BarStyle& barStyle,
		 const ValueRange<int>& range,
		 BindableValue<int>& value)
: m_Position(position),
m_Size(size),
//m_BarStyle(barStyle),
m_Range(range),
m_Value(value)
{
	m_Value.setBinding([this](const int newValue) { valueChanged(); });
}

//--------------------------------------------------------
void Bar::initUIElement(const Size& parentSize, const StyleSheet& styleSheet)
{
	auto bg = NodeCreator::createColourNode(PG::Colour(255, 255, 255), m_Size);
	bg->setPosition(m_Position);
	
	auto fg = NodeCreator::createColourNode(PG::Colour(0, 128, 255), Size(m_Size.width - 2, m_Size.height - 2));
	fg->setPosition(m_Position);
	
	m_Root.node->addChild(bg);
	m_Bar = m_Root.node->addChild(fg);
	
	valueChanged();
}

//--------------------------------------------------------
void Bar::valueChanged()
{
	if (!m_Bar.node)
	{
		return;
	}

	const auto value = MathsUtils::clamp(*m_Value, m_Range.start, m_Range.end);
	
	const auto widthPerUnit = m_Size.width / (float)m_Range.size();
	
	m_Bar.node->setSize(Size((widthPerUnit * value) - 2, m_Size.height - 2));
}

}
