
#import <Cocoa/Cocoa.h>
#include <string>

const char* utilGetBundleResourcePath(const char* name,const char*type){
  static char path[2048];
  NSBundle* myBundle = [NSBundle mainBundle];
  NSString* wallURL = [myBundle pathForResource:[NSString stringWithUTF8String:name]
 ofType:[NSString stringWithUTF8String:type]
];
  NSLog(@"%@",wallURL);
  std::string *bar = new std::string([wallURL UTF8String]);
  sprintf((char*)path,"%s",bar->c_str());
  delete bar;
  return (const char*)path;
}
