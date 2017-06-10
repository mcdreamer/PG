#include "PG/app/PGAppHost.h"
#include "PGTestAppController.h"

//--------------------------------------------------------
int main(int argc, const char * argv[])
{
    PGTestAppController testAppController;
    
    PG::PGAppHost appHost;
    appHost.runApp(testAppController);
    
    return 0;
}
