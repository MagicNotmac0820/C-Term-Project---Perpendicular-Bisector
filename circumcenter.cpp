#include <iostream>
#include "line.h"

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
    CLine l1 = PerpendicularBisector( p1 , p2 ) ;
    CLine l2 = PerpendicularBisector( p2 , p3 ) ;

    return l1.Intersect(l2) ;
}

int main(void){
    CPoint a , b , c ;
    cout << "Please input the first point (e.g. \"0 0\") -- " ; 
    cin >> a ;
    cout << "Please input the second point (e.g. \"3 0\") -- " ;
    cin >> b ;
    cout << "Please input the third point(e.g. \"0 3\") -- " ;
    cin >> c ;
    
    cout << findCircumcenterPoint( a , b , c ) << endl ;

    return EXIT_SUCCESS ;
}
