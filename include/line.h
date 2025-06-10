#ifndef __LINE_H__
#define __LINE_H__

#include <iostream>
#include <point.h>
using std::ostream ;

class CLine{
    private :
        CRational coefficient_a , coefficient_b , const_term ;
        CRational _slope ;
    public :
        CLine( CRational a , CRational b , CRational c ) ;
        CLine( CPoint point , CRational slope ) ;
        CLine( CPoint point1 , CPoint point2 ) ;
        CRational Slope(void)const ;
        CPoint Intersect( const CLine &l2 ) ;
    friend ostream &operator<<( ostream &ouput , const CLine &line ) ;        
} ;

/* ostream &operator<<( ostream &output , const CLine &line ){
    if( line.coefficient_a > 0 ){
        if( line.coefficient_a != 1 )
            output << line.coefficient_a << ' ' ;
        
        output << 'x' << ' ' ;
    }else if( line.coefficient_a < 0 ){
        output << '-' << ' ' ;
        if( line.coefficient_a != -1 )
            output << -line.coefficient_a << ' ' ;
        
        output << 'x' << ' ' ;
    }

    if( line.coefficient_b > 0 ){
        output << '+' << ' ' ;
        if( line.coefficient_b != 1 )
            output << line.coefficient_b << ' ' ;
        
        output << 'y' << ' ' ;
    }else if( line.coefficient_b < 0 ){
        output << '-' << ' ' ;
        if( line.coefficient_b != -1 )
            output << -line.coefficient_b << ' ' ;
        
        output << 'y' << ' ' ;
    }

    output << '=' << ' ' << line.const_term ;

    return output ;
} */
//The other version of operator<< overloading

ostream &operator<<( ostream &output , const CLine &line ){
    if( line.coefficient_a < 0 )
        output << '-' << ' ' ;
    
    if( line.coefficient_a != 0 && abs(line.coefficient_a) != 1 )
        output << abs(line.coefficient_a) << ' ' ;
        
    if( line.coefficient_a != 0 )
        output << 'x' << ' ' ;
        
    if( line.coefficient_b < 0 )
        output << '-' << ' ' ;
    else if( line.coefficient_b > 0 )
        output << '+' << ' ' ;
        
    if( line.coefficient_b != 0 && abs(line.coefficient_b) != 1 )
        output << abs(line.coefficient_b) << ' ' ;
        
    if( line.coefficient_b != 0 )
        output << 'y' << ' ' ;
        
    output << '=' << line.const_term ;
    return output ;
}


//Member functions of CLine
CLine::CLine( CRational a , CRational b , CRational c ){
    if( a == 0 && b == 0 )
        throw "Invalid Linear function!" ;
    if( a != 0 && b == 0 ){
        _slope = CRational::_undefined ;
        coefficient_a = 1 ;
        coefficient_b = 0 ;
        const_term = c / a ;
        return ;
    }

    _slope = -a/b ;
    coefficient_a = _slope.getNumerator() ;
    coefficient_b = -_slope.getDenominator() ;
    const_term = coefficient_b* c/b ;
}

CLine::CLine( CPoint point , CRational slope ){
    if(!slope.isValid()){
        _slope = slope ;
        coefficient_a = 1 ;
        coefficient_b = 0 ;
        const_term = point.getXCoordinate() ;

        return ;
    }

    slope.Reduction() ;
    _slope = slope ;
    coefficient_a = slope.getNumerator() ;
    coefficient_b = -slope.getDenominator() ;
    const_term = coefficient_a*point.getXCoordinate() +
                 coefficient_b*point.getYCoordinate() ;
}

CLine::CLine( CPoint point1 , CPoint point2 ){
    CRational x1 = point1.getXCoordinate() ;
    CRational x2 = point2.getXCoordinate() ;
    CRational y1 = point1.getYCoordinate() ;
    CRational y2 = point2.getYCoordinate() ;

    _slope = (y2-y1) / (x2-x1) ;
    if( _slope == CRational::_undefined ){
        coefficient_a = 1 ;
        coefficient_b = 0 ;
        const_term = x1 ;
        return ;
    }

    _slope.Reduction() ;
    coefficient_a = _slope.getNumerator() ;
    coefficient_b = -_slope.getDenominator() ;
    const_term = coefficient_a*x1 +
                 coefficient_b*y1 ;
}

CRational CLine::Slope(void)const {
    return _slope ;
}

CPoint CLine::Intersect( const CLine &l2 ){
    if( this->Slope() == l2.Slope() ){
        std::cout << "Can not find the intersection point of two parallel lines." << std::endl ;
        return {} ;
    }

    CRational x_coordinate = ( const_term*l2.coefficient_b - coefficient_b*l2.const_term ) /
                             ( coefficient_a*l2.coefficient_b - coefficient_b*l2.coefficient_a ) ;
    CRational y_coordinate = ( const_term*l2.coefficient_a - coefficient_a*l2.const_term ) /
                             ( coefficient_b*l2.coefficient_a - coefficient_a*l2.coefficient_b ) ;
    return CPoint( x_coordinate , y_coordinate ) ;
}

#endif  //__LINE_H__
