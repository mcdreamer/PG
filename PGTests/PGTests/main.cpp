#include <iostream>
#include "gtest/gtest.h"

#include "PG/io/IResourceHandler.h"

namespace PG {
namespace Internal {
    
extern int tileSize;
extern IResourceHandler* resourceHandler;
    
}
}

namespace
{
    //--------------------------------------------------------
    class TestResourceHandler : public PG::IResourceHandler
    {
    public:
        //--------------------------------------------------------
        virtual std::string getResourcePath(const std::string& name, const std::string& type) override
        {
            return name + "." + type;
        }
    };
}

//--------------------------------------------------------
GTEST_API_ int main(int argc, char **argv)
{
    printf("=======================================\n");
    printf(" * PG Tests\n");
    printf("=======================================\n\n");
    
    printf("\nSetting up...\n");
    
    TestResourceHandler testResHandler;
    PG::Internal::resourceHandler = &testResHandler;
    
    printf("Done.\n\n");
    
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
