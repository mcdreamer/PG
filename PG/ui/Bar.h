#pragma once

#include "PG/graphics/Node.h"
#include "PG/core/ValueRange.h"
#include "PG/core/Point.h"
#include "PG/core/Size.h"
#include "PG/core/BindableValue.h"
#include "PG/ui/PGUIElement.h"

namespace PG {

//--------------------------------------------------------
enum class BarStyle
{
	kBasic
};

//--------------------------------------------------------
class Bar : public PGUIElement
{
public:
	Bar(const PGPoint& position,
		const PGSize& size,
		const BarStyle& barStyle,
		const ValueRange<int>& range,
		BindableValue<int>& value);

	virtual void	initUIElement(const StyleSheet& styleSheet) override;
	virtual void	receiveTag(const int tag, PGUIMessageQueuePoster& msgPoster) override {}

private:
	PGPoint					m_Position;
	PGSize					m_Size;
	const BarStyle			m_BarStyle;
	const ValueRange<int>	m_Range;
	BindableValue<int>&		m_Value;
	NodeHandle				m_Bar;

	void valueChanged();
};

}
