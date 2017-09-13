#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <string>
using std::string;

#include <sstream>
using std::stringstream;

#include <iostream>
using std::endl;
using std::cout;
using std::ostream;

#include <cstring>

#include <cmath>

//���ڸ������Ƚ��Ƿ���ȵľ��� 
const double precision = 0.00001;

//����һ������ʽ�� 
class Polynomial {
		//��Ԫ�������������ʽ���գ�����=�������Ʋ��գ�anx^n+an-1x^n-1+...+a1x+a0 ��ʽ 
		friend ostream &operator<<( ostream &output, const Polynomial &polynomial );
	public:
		//ȱʡ���캯�� 
		Polynomial();
		//�������캯�� 
		Polynomial( const Polynomial &other );
		//һ��Ĺ��캯��������Ϊ����ʽ�ַ���������(5,6)(-4,3)(2,0)��ָ��Ϊ��Ȼ���ҵݼ����Ͷ���ʽ�����֣�Ĭ��Ϊ�գ� 
		Polynomial( const string &polynomial,const string &name = "" );
		//һ�㹹�캯�����ѳ���ת��Ϊ��ζ���ʽ�� 
		Polynomial( const double &num );
		//�������� 
		~Polynomial();

		//�������� 
		void setName( const string &name );
		//��ȡ���� 
		string getName() const;
		//��ȡ����ʽ���� 
		double *getData() const;
		//����ʽ�Ĵ��� 
		int degree() const;
		//�Զ���ʽ�� 
		Polynomial differentiate();
		//�Զ���ʽ��ֵ 
		double valueOfPolynomial( double num );

		//���ض���ʽ�ӷ� 
		Polynomial operator+( const Polynomial &op2 );
		//���ض���ʽ����
		Polynomial operator-( const Polynomial &op2 );
		//���ض���ʽ�ĸ��ŵ�Ԫ����� 
		Polynomial operator-();
		//���ض���ʽ�˷� 
		Polynomial operator*( const Polynomial &op2 );
		//���ض���ʽ��ֵ���� 
		Polynomial &operator=( const Polynomial &op2 );
		//�ж϶���ʽ�Ƿ���� 
		bool operator==( const Polynomial &op2 );
		//�ж϶���ʽ�Ƿ���� 
		bool operator!=( const Polynomial &op2 );
	private:
		//������˽�к����������ж������������Ƿ���� 
		bool isEqual( const double &a,const double &b );
		//����ʽ������ 
		string _name;
		//����ʽ�����ݱ�����_data�����У�������ai=n,���ʾ����Ϊnx^i; 
		double *_data;
		//_size��ʾ����ռ��С 
		int _size;
};

bool Polynomial::isEqual( const double &a,const double &b ) {
	if ( fabs( a - b ) < precision ) return true;
	return false;
}

Polynomial::Polynomial() {
	_name = "";
	_data = NULL;
	_size = 0;
}

Polynomial::Polynomial( const string &polynomial,const string &name ) {
	int i = polynomial.find( ",", 0 );
	int j = polynomial.find( ")", 0 );
	_size = atoi( polynomial.substr( i + 1, j - i - 1 ).c_str() ) + 1;

	_data = new double[ _size ];

	if ( _data ) {
		memset( _data, 0, _size * sizeof( double ) );
		int right = -1;
		int left = 0;
		while ( ( left = polynomial.find( "(", right + 1 ) ) != string::npos ) {
			int partition = polynomial.find( ",", right + 1 );
			right = polynomial.find( ")", right + 1 );
			double coefficient = atof( polynomial.substr( left + 1, partition - left - 1 ).c_str() );
			int degree = atoi( polynomial.substr( partition + 1, right - partition - 1 ).c_str() );
			_data[ degree ] = coefficient;
		}
	} else {
		cout << "No memory available!" << endl;
	}

	setName( name );
}

Polynomial::Polynomial( const double &num ) {
	_size = 1;
	stringstream name;
	name << num;
	name >> _name;
	_data = new double( num );

	if ( _data ) memset( _data, 0, _size * sizeof( double ) );
	else         cout << "No memory available!" << endl;

}

Polynomial::Polynomial( const Polynomial &other ) {
	_name = other._name;
	_size = other._size;

	_data = new double[ _size ];

	if ( _data ) {
		memset( _data, 0, _size * sizeof( double ) );
		for ( int i = 0; i < _size; ++i )
			_data[ i ] = other._data[ i ];
	} else {
		cout << "No memory available!" << endl;
	}

}

Polynomial::~Polynomial() {
	_name = "";
	if ( _data ) {
		delete []_data;
		_data = NULL;
	}
	_size = 0;
}

void Polynomial::setName( const string &name ) {
	_name = name;
}

string Polynomial::getName() const {
	return _name;
}

double *Polynomial::getData() const {
	return _data;
}

int Polynomial::degree() const {

	if ( !_data )
		return 0;
	else {
		for ( int i = _size - 1; i >= 0; --i ) {
			if ( _data[ i ] ) {
				return i;
				break;
			}
		}
	}

	return 0;
}

Polynomial Polynomial::differentiate() {
	Polynomial diff( *this );
	diff.setName( "" );

	if ( this->degree() == 0 )
		diff.getData()[ 0 ] = 0;
	else {
		int degree = this->degree();

		for ( int i = 0; i <= degree - 1; ++i )
			diff.getData()[ i ] = diff.getData()[ i + 1 ] * ( i + 1 );
		diff.getData()[ degree ] = 0;
	}

	return diff;
}

double Polynomial::valueOfPolynomial( double num ) {
	int degree = this->degree();
	double value = 0;
	for ( int i = degree; i >= 0; --i )
		value += _data[ i ] * pow( num, i );
	return value;
}

Polynomial Polynomial::operator+( const Polynomial &op2 ) {
	int degree1 = this->degree();
	int degree2 = op2.degree();

	Polynomial temp( degree1 > degree2 ? *this : op2 );
	temp.setName( "" );

	for ( int i = 0; i <= degree1 && i <= degree2 ; ++i )
		temp._data[ i ] = this->_data[ i ] + op2._data[ i ];

	return temp;
}

Polynomial Polynomial::operator-( const Polynomial &op2 ) {
	Polynomial right( op2 );
	for ( int i = 0; i < right._size; ++i )
		right._data[ i ] *= -1;
	Polynomial temp = *this + right;
	temp.setName( "" );
	return temp;
}

Polynomial Polynomial::operator-() {
	Polynomial temp( *this );
	temp.setName( "-" + this->_name );

	for ( int i = 0; i < _size; ++i )
		temp._data[ i ] *= -1;

	return temp;
}

Polynomial Polynomial::operator*( const Polynomial &op2 ) {
	int degree1 = this->degree();
	int degree2 = op2.degree();

	Polynomial temp;
	temp._size = degree1 + degree2 + 1;
	temp._name = "";
	temp._data = new double[ temp._size ];

	if ( _data ) {
		memset( temp._data, 0, temp._size * sizeof( double ) );
		for ( int i = 0; i <= degree1; ++i )
			for ( int j = 0; j <= degree2; ++j )
				temp._data[ i + j ] += this->_data[ i ] * op2._data[ j ];
	} else {
		cout << "No memory available!" << endl;
	}

	return temp;
}

bool Polynomial::operator==( const Polynomial &op2 ) {
	if ( this->degree() != op2.degree() )
		return false;

	for ( int i = this->degree(); i >= 0; --i )
		if ( !isEqual( this->getData()[ i ], op2.getData()[ i ] ) )
			return false;

	return true;
}

bool Polynomial::operator!=( const Polynomial &op2 ) {
	return !( *this == op2 );
}

Polynomial &Polynomial::operator=( const Polynomial &op2 ) {
	if ( this->_data ) delete []_data;
	this->_size = op2._size;
	this->_name = op2._name;
	this->_data = new double[ this->_size ];

	if ( this->_data ) {
		memset( _data, 0, _size * sizeof( double ) );
		for ( int i = 0; i < _size; ++i )
			_data[ i ] = op2._data[ i ];
	}
	return *this;
}

ostream &operator<<( ostream &out, const Polynomial &polynomial ) {
	if ( polynomial.getName() != "" ) out << polynomial.getName() << "=";

	double constant = polynomial.getData()[ 0 ];
	int degree = polynomial.degree();

	if ( degree == 0 )
		out << constant;
	else {
		double highestDegreeCoef = polynomial.getData()[ degree ];

		if ( !( highestDegreeCoef == 1 || highestDegreeCoef == -1 ) ) out << highestDegreeCoef << "x";
		else if ( highestDegreeCoef == -1 )     					  out << "-x";
		else if ( highestDegreeCoef == 1 )							  out << "x";

		if ( degree != 1 ) out << "^" << degree;

		for ( int i = degree - 1; i > 0; --i ) {
			double coefficient = polynomial.getData()[ i ];
			if ( !coefficient ) continue;

			if ( !( coefficient == 1 || coefficient == -1) ) {

				if ( i != 1 ) out << ( coefficient > 0 ? "+" : "" ) << coefficient << "x^" << i;
				else          out << ( coefficient > 0 ? "+" : "" ) << coefficient << "x";

			} else {

				if ( i != 1 ) out << ( coefficient > 0 ? "+" : "-" ) << "x^" << i;
				else		  out << ( coefficient > 0 ? "+" : "-" ) << "x";

			}

		}

		if ( constant ) out << ( constant > 0 ? "+" : "" ) << constant;
	}

	return out;
}

#endif
