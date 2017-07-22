#pragma once

#include "PG/ui/UIElement.h"

namespace PG {

//--------------------------------------------------------
class Dialog : public UIElement
{
public:
    virtual void initUIElement(const StyleSheet& styleSheet) override final;

    virtual void setupDialog(NodeHandle root)=0;
};

}
