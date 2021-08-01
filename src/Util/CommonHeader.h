//
// Created by Joseph Alai on 7/28/21.
//

#ifndef ENGINE_COMMONHEADER_H
#define ENGINE_COMMONHEADER_H
#include <iostream>
#define FOR(q,n) for(int q=0;q<n;q++)
#define SFOR(q,s,e) for(int q=s;q<=e;q++)
#define RFOR(q,n) for(int q=n;q>=0;q--)
#define RSFOR(q,s,e) for(int q=s;q>=e;q--)

#define ESZ(elem) (int)elem.size()

#define PRINT(x) std::cout << " " << (x)
#define PRINT_HX(h,x) PRINT(h) << ": " << ", " << (x)
#define PRINT_X(x) PRINT_HX(#x,x)
#define PRINT_HXT(h,x,t) PRINT_HX(h,x) << ", " << (t)
#define PRINT_FOUR(h,x,t,r) PRINT_HXT(h,x,t) << ", " << (r)
#define PRINT_FIVE(h,x,t,r,s) PRINT_FOUR(h,x,t,r) << ", " << (s)
#define PRINT_SIX(h,x,t,r,s,l) PRINT_FIVE(h,x,t,r,s) << ", " << (l)
#define PRINT_SEVEN(h,x,t,r,s,l,n) PRINT_SIX(h,x,t,r,s,l) << ", " << (n)
#define PRINT_EIGHT(h,x,t,r,s,l,n,q) PRINT_SEVEN(h,x,t,r,s,l,n) << ", " << (q)

#define PRINTLN(x) PRINT(x) << '\n'
#define PRINT_HXLN(h,x) PRINT_HX(h,x) << '\n'
#define PRINT_XLN(x) PRINT_HXLN(#x,x)
#define PRINT_HXTLN(h,x,t) PRINT_HXT(h,x,t) << '\n'
#define PRINT_FOURLN(h,x,t,r) PRINT_FOUR(h,x,t,r) << '\n'
#define PRINT_FIVELN(h,x,t,r,s)  PRINT_FIVE(h,x,t,r,s)  << '\n'
#define PRINT_SIXLN(h,x,t,r,s,l)  PRINT_SIX(h,x,t,r,s,l)  << '\n'
#define PRINT_SEVENLN(h,x,t,r,s,l,n)  PRINT_SEVEN(h,x,t,r,s,l,n)  << '\n'
#define PRINT_EIGHTLN(h,x,t,r,s,l,n,q) PRINT_EIGHT(h,x,t,r,s,l,n,q) << '\n'

#define PI 3.14159265359
#define DEGREES(radians) ((radians) * 180 / PI)
#define RADIANS(degrees) ((degrees) * PI / 180)
#define ABS(x) ((x) < 0 ? (-(x)) : (x))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#endif //ENGINE_COMMONHEADER_H
