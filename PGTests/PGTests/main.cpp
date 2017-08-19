#include <iostream>
#include "gtest/gtest.h"

#include "PG/io/IResourceHandler.h"
#include "PG/internal/graphics/SFMLNode.h"
#include "TestResourceHandler.h"

namespace PG {
namespace Internal {
    
extern int g_TileSize;
extern IResourceHandler* g_ResourceHandler;
extern SFMLFontCache* g_FontCache;
    
}
}

//--------------------------------------------------------
GTEST_API_ int main(int argc, char **argv)
{
    printf("=======================================\n");
    printf(" * PG Tests\n");
    printf("=======================================\n\n");
    
    printf("\nSetting up...\n");
    
    TestResourceHandler testResHandler;
	PG::Internal::SFMLFontCache fontCache;
    PG::Internal::g_ResourceHandler = &testResHandler;
	PG::Internal::g_FontCache = &fontCache;
    
    printf("Done.\n\n");
    
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
