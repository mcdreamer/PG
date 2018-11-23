#pragma once

#include "PG/graphics/Node.h"
#include "PG/core/ValueRange.h"
#include "PG/core/Point.h"
#include "PG/core/Size.h"
#include "PG/core/BindableValue.h"
#include "PG/ui/UIElement.h"

namespace PG {

//--------------------------------------------------------
enum class BarStyle
{
	kBasic
};

//--------------------------------------------------------
class Bar : public UIElement
{
public:
	Bar(const Point& position,
		const Size& size,
		const BarStyle& barStyle,
		const ValueRange<int>& range,
		BindableValue<int>& value);

	virtual void	initUIElement(const StyleSheet& styleSheet) override;

private:
	Point					m_Position;
	Size					m_Size;
	const BarStyle			m_BarStyle;
	const ValueRange<int>	m_Range;
	BindableValue<int>&		m_Value;
	NodeHandle				m_Bar;

	void valueChanged();
};

}
