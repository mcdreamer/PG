#pragma once

#include "PG/ui/PGUIElement.h"

namespace PG {

//--------------------------------------------------------
class PGDialog : public PGUIElement
{
public:
    virtual void init(const StyleSheet& styleSheet) override final;

    virtual void setupDialog(NodeHandle root)=0;
};

}
