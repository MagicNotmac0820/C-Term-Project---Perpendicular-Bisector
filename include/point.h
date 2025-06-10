#ifndef __POINT_H__
#define __POINT_H__

#include <rational.h>

class CPoint{
    private :
        CRational m_x , m_y ;
    public :
        CPoint( CRational num1 = CRational() , CRational num2 = CRational() ) ;
        CPoint( int num1 , int num2 ) ;
        CPoint( string num1 , string num2 ) ;
        CPoint Midpoint( const CPoint &p2 )const ;
        bool operator==( const CPoint &p2 )const ;
        CRational getXCoordinate(void) ;
        CRational getYCoordinate(void) ;
    friend istream &operator>>( istream &input , CPoint &point ) ;
    friend ostream &operator<<( ostream &output , const CPoint &point ) ;
} ;

istream &operator>>( istream &input , CPoint &point ){
    string x_coordinate , y_coordinate ;
    input >> x_coordinate >> y_coordinate ;
    if(input.eof())
        throw("Invalid input: End of file detected. Aborted.") ;

    point = CPoint( x_coordinate , y_coordinate ) ;
    
    return input ;
}

ostream &operator<<( ostream &output , const CPoint &point ){
    output << '(' << point.m_x << ',' ;
    output << point.m_y << ')' ;

    return output ;
}

//Member functions of CPoint
CPoint::CPoint( CRational num1 , CRational num2 ) :
                m_x(num1) , m_y(num2){}

CPoint::CPoint( int num1 , int num2 ) :
                m_x(CRational(num1)) , m_y(CRational(num2)){}

CPoint::CPoint( string num1 , string num2 ) :
                m_x(CRational(num1)) , m_y(CRational(num2)){}

CPoint CPoint::Midpoint( const CPoint &p2 )const {
    CRational newPos_x = (m_x+p2.m_x) / 2 ;
    CRational newPos_y = (m_y+p2.m_y) / 2 ;
    CPoint result( newPos_x , newPos_y ) ;

    return result ;
}

bool CPoint::operator==( const CPoint &p2 )const {
    return ( m_x == p2.m_x ) && ( m_y == p2.m_y ) ;
}

CRational CPoint::getXCoordinate(void){
    return m_x ;
}

CRational CPoint::getYCoordinate(void){
    return m_y ;
}

#endif  //__POINT_H__
