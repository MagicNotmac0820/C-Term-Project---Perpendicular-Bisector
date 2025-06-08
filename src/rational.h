#ifndef __RATIONAL_H__
#define __RATIONAL_H__

#include <iostream>
#include <string>
#include <climits>
using std::istream ;
using std::ostream ;
using std::string ;
using std::cin ;
using std::cout ;
using std::endl ;

int gcd( int num1 , int num2 ) ;

class CRational ;
class CRational{
    private :
        int m_numerator ;
        int m_denominator ;
    public :
        static const CRational _undefined ;

        CRational( int n = 0 , int d = 1 ) ;
        CRational( const CRational &num ) ;
        CRational( string str ) ;
        void Reduction(void) ;
        int getNumerator(void)const ;
        int getDenominator(void)const ;
        bool isValid(void)const ;
        CRational operator+(void)const ;
        CRational operator-(void)const ;
        CRational &operator=( const CRational & ) ;
        bool operator>( const CRational & )const ;
        bool operator<( const CRational & )const ;
        bool operator==( const CRational & )const ;
        bool operator!=( const CRational & )const ;
        CRational Add( const CRational & )const ;
        CRational Substract( const CRational & )const ;
        CRational Multiply( const CRational & )const ;
        CRational Divide( const CRational & )const ;
        CRational operator+( const CRational & )const ;
        CRational operator-( const CRational & )const ;
        CRational operator*( const CRational & )const ;
        CRational operator/( const CRational & )const ;
    friend istream &operator>>( istream & , CRational & ) ;
    friend ostream &operator<<( ostream & , const CRational & ) ;
    friend CRational abs( const CRational & ) ;
} ;
const CRational CRational::_undefined = static_cast<CRational>(INT_MAX) ;

int gcd( int num1 , int num2 ){
    if(!num2)
        return num1 ;
    
    return gcd( num2 , num1%num2 ) ;
}

istream &operator>>( istream &input , CRational &num ){
    input >> num.m_numerator >> num.m_denominator ;
    return input ;
}

ostream &operator<<( ostream &output , const CRational &num ){
    if( num.m_denominator == 1 || !num.m_numerator ){
        output << num.m_numerator ;
        return output ;
    }
    
    output << num.m_numerator << '/'<< num.m_denominator ;
    return output ;
}

CRational abs( const CRational &num ){
    return CRational( abs(num.m_numerator) , abs(num.m_denominator) ) ;
}

//Member functions of CRational
CRational::CRational( int n , int d ) : m_numerator(n) , m_denominator(d)
{ if(!d)  *this = _undefined ; }

CRational::CRational( const CRational &num ) :
                      m_numerator(num.m_numerator) , m_denominator(num.m_denominator)
{
    if(!num.isValid())
        *this = _undefined ;
}

CRational::CRational( string str ){
    size_t index = str.find('/') ;
    string m_numerator_str = str.substr(0,index) ;
    string m_denominator_str ;
    if( m_numerator_str.find_first_not_of("0123456789+-") != string::npos ||
        ( m_numerator_str.find("+") != m_numerator_str.rfind("+") ) ||
        ( m_numerator_str.find("-") != m_numerator_str.rfind("-") ) )
        throw("Invalid input: The string to construct \"CRational\" should be a valid number of fraction.");

    if( index == str.npos ){
        m_numerator = stoi(m_numerator_str) ;
        m_denominator = 1 ;
        return ;
    }
    m_denominator_str = str.substr(index+1) ;
    if( m_denominator_str.find_first_not_of("0123456789+-") != string::npos ||
        ( m_denominator_str.find("+") != m_denominator_str.find("+") ) ||
        ( m_denominator_str.find("-") != m_denominator_str.find("-") ) )
        throw("Invalid input: The string to construct \"CRational\" should be a valid number of fraction.") ;

    m_numerator = stoi(m_numerator_str) ;
    m_denominator = stoi(m_denominator_str) ;

    if(!isValid())  *this = _undefined ;
}

void CRational::Reduction(void){
    if( !m_numerator || !isValid() )
        return ;
        
    int gcdNum = ( m_numerator < 0 ) ? gcd( m_denominator , m_numerator ) :
                                       gcd( m_numerator , m_denominator ) ;
    m_numerator /= gcdNum ;
    m_denominator /= gcdNum ;

    return ;
}

int CRational::getNumerator(void)const {
    return m_numerator ;
}

int CRational::getDenominator(void)const {
    return m_denominator ;
}

bool CRational::isValid(void)const {
    return ( m_denominator && 
           ( m_numerator != INT_MAX || m_denominator != 1 ) ) ;
}

CRational CRational::operator+(void)const {
    return *this ;
}

CRational CRational::operator-(void)const {
    if(!isValid())
        return _undefined ;

    return CRational(-m_numerator,m_denominator) ;
}

CRational &CRational::operator=( const CRational &b ){
    if( this == &b )
        return *this ;
    if(!b.isValid()){
        m_numerator = INT_MAX ; //return a reference of inValid CRational
        m_denominator = 1 ;
        return *this ;
    }

    m_numerator = b.m_numerator ;
    m_denominator = b.m_denominator ;
    return *this ;
}

bool CRational::operator>( const CRational &b )const  {
    if( !isValid() || !b.isValid() )
        return false ;

    return ( m_numerator*b.m_denominator > m_denominator*b.m_numerator ) ;
}

bool CRational::operator<( const CRational &b )const {
    if( !isValid() || !b.isValid() )
        return false ;

    return ( m_numerator*b.m_denominator < m_denominator*b.m_numerator ) ;
}

bool CRational::operator==( const CRational &b )const {
    if( !isValid() || !b.isValid() )
        return false ;

    CRational tmp1 = *this ;
    CRational tmp2 = b ;
    tmp1.Reduction() ;
    tmp2.Reduction() ;

    return ( tmp1.m_numerator == tmp2.m_numerator ) &&
           ( tmp1.m_denominator == tmp2.m_denominator ) ;
}

bool CRational::operator!=( const CRational &b )const {
    if( !isValid() || !b.isValid() )
        return true ;

    return !operator==(b) ;
}

CRational CRational::Add( const CRational &num )const {
    if( !isValid() || !num.isValid() )
        return _undefined ;

    int newNumerator = m_numerator*num.m_denominator +
                       m_denominator*num.m_numerator ;
    int newDenominator = m_denominator * num.m_denominator ;
    CRational result( newNumerator , newDenominator ) ;
    result.Reduction() ;

    return result ;
}

CRational CRational::Substract( const CRational &num )const {
    if( !isValid() || !num.isValid() )
        return _undefined ;
    
    int newNumerator = m_numerator*num.m_denominator -
                       m_denominator*num.m_numerator ;
    int newDenominator = m_denominator * num.m_denominator ;
    CRational result( newNumerator , newDenominator ) ;
    result.Reduction() ;

    return result ;
}

CRational CRational::Multiply( const CRational &num )const {
    if( !isValid() || !num.isValid() )
        return _undefined ;

    int newNumerator = m_numerator * num.m_numerator ;
    int newDenominator = m_denominator * num.m_denominator ;
    CRational result( newNumerator , newDenominator ) ;
    result.Reduction() ;

    return result ;
}

CRational CRational::Divide( const CRational &num )const {
    if( !isValid() || !num.isValid() || num == 0 )
        return _undefined ;

    int newNumerator = m_numerator * num.m_denominator ;
    int newDenominator = m_denominator * num.m_numerator ;
    CRational result( newNumerator , newDenominator ) ;
    result.Reduction() ;

    return result ;
}

CRational CRational::operator+( const CRational &num )const {
    return Add(num) ;
}

CRational CRational::operator-( const CRational &num )const {
    return Substract(num) ;
}

CRational CRational::operator*( const CRational &num )const {
    return Multiply(num) ;
}

CRational CRational::operator/( const CRational &num )const {
    return Divide(num) ;
}

#endif  //__RATIONAL_H__
