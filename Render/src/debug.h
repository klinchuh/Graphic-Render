#ifndef DEBUG_H
#define DEBUG_H

//full debug output log
#define DEBUG_LOG 


#ifdef DEBUG_LOG

#include <iostream>
#include <fstream>

extern std::ofstream __debug_s;

#define ERROR_FLT(x) __debug_s << __FILE__ << ":" << __LINE__ << "\nError:" << x << std::endl;

#define DEBUG_S(x) __debug_s << x << std::endl;

#endif // !DEBUG_LOG

#ifndef DEBUG_LOG

#define ERROR_FLT(x) ;

#define DEBUG_S(x) ;

#endif // !DEBUG_LOG


#endif // !DEBUG_H