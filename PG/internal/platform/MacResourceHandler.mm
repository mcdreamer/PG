#include "MacResourceHandler.h"

#import <Foundation/Foundation.h>

namespace PG {
namespace Internal {

namespace
{
    //--------------------------------------------------------
    std::string nsStringToStdString(NSString* nsString)
    {
        return nsString ? [nsString UTF8String] : std::string();
    }

    //--------------------------------------------------------
    NSString* stdStringToNSString(const std::string& string)
    {
        return [NSString stringWithUTF8String:string.c_str()];
    }
}

//--------------------------------------------------------
std::string MacResourceHandler::getResourcePath(const std::string& name, const std::string& type)
{
    NSString* f = stdStringToNSString(name);
    NSString* t = stdStringToNSString(type);
    
    NSBundle* mainBundle = [NSBundle mainBundle];

    return nsStringToStdString([mainBundle pathForResource:f ofType:t]);
}

}
}
