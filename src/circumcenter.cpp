#include <iostream>
#include "line.h"
#define RED "\x1B[1;38;5;196m"
#define DEFAULT "\x1B[0;m"
// #define MULTIPLE_TESTCASE

CLine PerpendicularBisector( const CPoint &point1 , const CPoint &point2 ){
    CLine line12( point1 , point2 ) ;
    CPoint midPoint = point1.Midpoint(point2) ;

    CRational slopeOfLine ;
    if(!line12.Slope().isValid())
        slopeOfLine = 0 ;
    else
        slopeOfLine = static_cast<CRational>(-1) / line12.Slope() ;

    return CLine( midPoint , slopeOfLine ) ;
}

CPoint findCircumcenterPoint( const CPoint &p1 , const CPoint &p2 , const CPoint &p3 ){
    if( p1 == p2 || p2 == p3 || p3 == p1 )
        throw("Circumcenter computation failed: Duplicate points detected.") ;

    CLine l1 = PerpendicularBisector( p1 , p2 ) ;
    CLine l2 = PerpendicularBisector( p2 , p3 ) ;

    if( ( l1.Slope() == l2.Slope() ) || ( !l1.Slope().isValid() && !l2.Slope().isValid() ) )
        throw("Circumcenter computation failed: Perpendicular bisectors are parallel or coincident.") ;

    return l1.Intersect(l2) ;
}

int main(void){
    CPoint a , b , c ;
#ifdef MULTIPLE_TESTCASE
    int testcase_num = 0 ;
#endif

#ifdef MULTIPLE_TESTCASE
    while(1){
#endif
        try{
            cin >> a >> b >> c ;
        }catch( const char *error_msg ){
            cout << RED << error_msg << DEFAULT << endl ;

#ifdef MULTIPLE_TESTCASE
            if(cin.eof())
                break ;
            continue ;
#else
            return EXIT_FAILURE ;
#endif
        }

        CPoint result ;

        try{
            result = findCircumcenterPoint( a , b , c ) ;

#ifdef MULTIPLE_TESTCASE
            printf("Case %d: ", ++testcase_num ) ;
#endif
            cout << result << endl ;
        }catch( const char *error_msg ){
            cout << RED << error_msg << DEFAULT << endl ;
#ifdef MULTIPLE_TESTCASE
            continue ;
#else
            return EXIT_FAILURE ;
#endif
        }

#ifdef MULTIPLE_TESTCASE
    }
#endif

    return EXIT_SUCCESS ;
}

/* 
0 0
4 0
2 3

0 0
2 3
4 0

4 0
0 0
2 3

4 0
2 3
0 0

2 3
0 0
4 0

2 3
4 0
0 0
*/