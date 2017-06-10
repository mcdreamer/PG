#pragma once

#include "PG/ui/PGUIElement.h"

namespace PG {

//--------------------------------------------------------
class PGDialog : public PGUIElement
{
public:
    virtual void init() override final;

    virtual void setupDialog(NodeHandle root)=0;
};

}
