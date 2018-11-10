#include "PG/app/PGAppHost.h"
#include "AppController.h"

//--------------------------------------------------------
int main(int argc, const char * argv[])
{
    AppController testAppController;
    
    PG::PGAppHost appHost;
    appHost.runApp(testAppController);
    
    return 0;
}
