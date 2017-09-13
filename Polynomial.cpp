#include <iostream>
#include <vector>
#include <conio.h>
#include <sstream>
#include "Polynomial.h"
using namespace std;

//����ʽ���� 
vector<Polynomial> record;
//�������� 
enum RequestType { QUIT = '0', INPUT, ADD, SUBTRACT, MULTI, DIFF, VALUE, ISEQUALTO, SHOW, };

//�û����룬��ʽΪ�� ����ʽ����=(ϵ����ָ��)(ϵ����ָ��)...(ϵ����ָ��)������ָ��Ϊ��Ȼ�����ҽ�������,���벻���ո� 
void input();
//����ʽ���㣬���ӡ������� 
void operation( char oper );
//����ʽ�� 
void diff();
//����ʽ��ֵ 
void value();
//չʾ���ж���ʽ 
void show();
//�����ʾ��Ϣ 
void help();
//����������ʽ����ʾ��Ϣ������ 
void example();
//�ж���������ʽ�Ƿ���� 
void isEqualTo();
//input���Ӻ��� 
bool getPolynomial();
//��ȡ������
Polynomial getOperand( int i );
//��������Ķ���ʽ 
void save( const string &name, const string &poly );
//���������� 
bool saveNew( Polynomial newPoly );
//�������а�������������ʽ�������±� 
int findPoly( const string &name );
//�ж������Ƿ�Ϸ�������p=(5,6)(-4,3)(2,0)�Ϸ� 
bool isValidWithName( const string &str );
//�ж϶���ʽ��ż���Ƿ�Ϸ������� (5,6)(-4,3)(2,0)�Ϸ� 
bool isValidPoly( const string &str );
//�ж϶���ʽ��ż���Ƿ��ǽ������룬����(2,3)(2,4)���Ϸ� 
bool isValidExp( const string &str );

int main() {
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << 
			"                                               ��ӭʹ�ö���ʽ������!" << endl;
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n" << 
			"                                                                                                  -----�밴�س������˵�" << endl; 
	
	while ( getch() != 13 );
	system( "cls" );
	while ( true ) {
		help();
		char request;
		request = getch();
		switch ( request ) {
			case INPUT:
				input();
				break;

			case ADD:
				operation( '+' );
				break;

			case SUBTRACT:
				operation( '-' );
				break;

			case MULTI:
				operation( '*' );
				break;

			case DIFF:
				diff();
				break;

			case VALUE:
				value();
				break;

			case ISEQUALTO:
				isEqualTo();
				break;

			case SHOW:
				show();
				break;

			case QUIT:
				system( "cls" );
				cout << "\n��лʹ�ö���ʽ��������" << endl;
				return 0;
				break;

			case 13:
				system( "cls" );
				break;

			default :
				system( "cls" );
				cout << "\n�޴�ѡ�����������!" << endl;
				cout << "*********************" << endl;
				break;
		}
	}
	return 0;
}

void help() {
	cout << "\n����������������ʵ�֣�" << endl;
	cout << "[1] �������ʽ" << endl;
	cout << "[2] ����ʽ�ӷ�" << endl;
	cout << "[3] ����ʽ����" << endl;
	cout << "[4] ����ʽ�˷�" << endl;
	cout << "[5] ����ʽ��" << endl;
	cout << "[6] ����ʽ��ֵ" << endl;
	cout << "[7] �ж϶���ʽ�Ƿ����" << endl;
	cout << "[8] ��ʾ���ж���ʽ" << endl;
	cout << "[0] �˳�" << endl;
}

void show() {
	system( "cls" );
	if ( record.empty() )
		cout << "��\n\n���س��������˵�";
	else {
		cout << "����Ϊ���ж���ʽ��" << endl;
		for ( int i = 0; i < record.size(); ++i )
			cout << record[ i ] << endl;
		cout <<  "\n���س��������˵�";
	}
	while ( getch() != 13 );
	system( "cls" );
}

void example() {
	cout << "\n���������ʽ,��ʽΪ��" << endl;
	cout << "\n����ʽ����=(ϵ����ָ��)(ϵ����ָ��)...(ϵ����ָ��) " << endl;
	cout << "(ָ��Ϊ��Ȼ�����ҽ�������,���벻���ո�" << endl;
	cout << "\n���磺p=(5,6)(-4,3)(2,0)����ʾp=5x^6-4x^3+2" << endl;
	cout << "*****************************************************" << endl;
}

void input() {
	system( "cls" );
	example();
	while ( true ) if ( !getPolynomial() ) return;
}

Polynomial getOperand( int i ) {
	Polynomial op;
label :
	cout << "���������ʽ";
	if ( i ) cout << i;
	cout << "(���ƻ��µĶ���ʽ������0�������˵�)��";
	string poly;
	getline( cin, poly );
	if ( poly == "0" ) {
		system( "cls" );
		op.setName( "invalid" );
		return op;
	}

	if ( isValidPoly( poly ) && isValidExp( poly ) )
		op = poly;
	else {
		int index = findPoly( poly );

		if ( index == -1 ) {
			cout << "�����ڴ˶���ʽ�������ʽ����\n" << endl;
			goto label;
		} else
			op = record[ index ];

	}
	return op;
}

void operation( char oper ) {
	system( "cls" );
	Polynomial op1, op2;
	while ( true ) {
		Polynomial op1 = getOperand( 1 );
		if ( op1.getName() == "invalid" ) break;
		Polynomial op2 = getOperand( 2 );
		if ( op2.getName() == "invalid" ) break;

		Polynomial res;
		switch( oper ) {
			case '+': {
				res = op1 + op2;
				break;
			}
			case '-': {
				res = op1 - op2;
				break;
			}
			case '*': {
				res = op1 * op2;
				break;
			}
		}

		if ( op1.getName() != "" ) cout << op1.getName();
		else 					   cout << op1;

		cout << oper;

		if ( op2.getName() != "" ) cout << op2.getName();
		else 					   cout << op2;

		cout << "=" << res << endl << endl;
		if ( !saveNew( res ) ) {
			system( "cls" );
			break ;
		}
	}
}

void isEqualTo() {
	system( "cls" );
	Polynomial op1, op2;
	while ( true ) {
		Polynomial op1 = getOperand( 1 );
		if ( op1.getName() == "invalid" ) break;
		Polynomial op2 = getOperand( 2 );
		if ( op2.getName() == "invalid" ) break;

		if ( op1.getName() != "" ) cout << op1.getName();
		else 					   cout << op1;

		cout << ( op1 == op2 ? "=" : "!=" );

		if ( op2.getName() != "" ) cout << op2.getName() << endl << endl;
		else 					   cout << op2 << endl << endl;
	}
}

bool saveNew( Polynomial res ) {
	cout << "�Ƿ񱣴�����\n[1] ��\n[2] ���ǡ�\n�����룺";

	while ( true ) {
		char choice;
		cin >> choice;
		switch ( choice ) {
			case '2': {
				getchar();
				cout << endl;
				return true;
			}

			case '1': {
				cout << "������˶���ʽ������(����0�������˵�)��";
				string name;
				cin >> name;
				getchar();
				if ( name ==  "0" ) return false;
				while ( findPoly( name ) != -1 ) {
					cout << "�Բ�������\"" << name << "\"" << "�Ѵ��ڣ��������������ʽ�����֣� ";
					cin >> name;
					getchar();
					if ( name ==  "0" ) return false;
				}
				res.setName( name );
				record.push_back( res );
				cout << "����ɹ���\n" << endl;
				return true;
			}

			default:
				cout << "�޴�ѡ����������룺";
				break;
		}
	}
}

void diff() {
	system( "cls" );
	while ( true ) {
		Polynomial op = getOperand( 0 );
		if ( op.getName() == "invalid" ) {
			system( "cls" );
			break;
		}

		if ( op.getName() != "" ) cout << op.getName() << "\'=" << op.differentiate() << endl << endl;
		else 					  cout << "(" << op << ")\'=" << op.differentiate() << endl << endl;

	}
}

void value() {
	system( "cls" );
	while ( true ) {
		cout << "���������ʽ(���ƻ��µĶ���ʽ������0�������˵�)��";
		string poly;
		getline( cin, poly );
		if ( poly == "0" ) {
			system( "cls" );
			break;
		}

		if ( isValidPoly( poly ) && isValidExp( poly ) ) {

			Polynomial temp( poly );
			double num;
			cout << "������һ����(����0�˻����˵�)��";
			cin >> num;
			getchar();
			if ( num == 0 ) {
				system( "cls" );
				break;
			}
			cout << "x=" << num << "ʱ��" << temp << "=" << temp.valueOfPolynomial( num ) << endl << endl;
		} else {
			int index = findPoly( poly );
			if ( index == -1 )
				cout << "�����ڴ˶���ʽ�������ʽ����\n" << endl;
			else {
				double num;
				cout << "������һ����(����0�˻����˵�)��";
				cin >> num;
				getchar();
				if ( num == 0 ) {
					system( "cls" );
					break;
				}
				cout << "x=" << num << "ʱ��" << poly << "(" << num << ")" << "=" << record[ index ].valueOfPolynomial( num ) << endl << endl;
			}

		}

	}
	return;
}

bool getPolynomial() {
	string polynomialWithName;
	cout << "\n����ʽ(����0�������˵�): ";

	getline( cin, polynomialWithName );
	if ( polynomialWithName == "0" ) {
		system( "cls" );
		return false;
	}

	while ( !isValidWithName( polynomialWithName ) ) {
		cout << "�����ʽ����!�������������ʽ(����0�������˵�): ";
		getline( cin, polynomialWithName );
		if ( polynomialWithName == "0" ) {
			system( "cls" );
			return false;
		}
	}
	int equ = polynomialWithName.find( "=" );
	string polyName = polynomialWithName.substr( 0, equ );
	string poly = polynomialWithName.substr( equ + 1, polynomialWithName.length() - equ - 1 );

	save( polyName, poly );
	return true;
}

void save( const string &name, const string &poly ) {
	string n = name;
	while ( findPoly( n ) != -1 ) {
		cout << "�Բ�������\"" << name << "\"" << "�Ѵ��ڣ��������������ʽ�����֣� ";
		cin >> n;
		getchar();
	}


	Polynomial temp( poly, n );
	record.push_back( temp );
}

int findPoly( const string &name ) {
	for ( int i = 0; i != record.size(); ++i ) {
		if ( record[ i ].getName() == name )
			return i;
	}

	return -1;
}

bool isValidWithName( const string &str ) {
	int equ = str.find( "=" );

	if ( equ == string::npos )
		return false;

	if ( str.find( " " ) != string::npos )
		return false;

	string polyName = str.substr( 0, equ );
	if ( polyName == "" )
		return false;

	string poly = str.substr( equ + 1, str.length() - equ - 1 );

	return isValidPoly( poly ) && isValidExp( poly );
}

bool isValidPoly( const string &str ) {
	if ( str == "" )
		return false;

	if ( str.find( "(" ) != 0 || str.find( ",", 2 ) == string::npos || str.find( ")", 4 ) == string::npos )
		return false;

	int left = 0;
	int comma = str.find( "," );
	int right = str.find( ")" );
	double c;
	int e;
	string coef = str.substr( 1, comma - 1 );
	string exp = str.substr( comma + 1, right - comma - 1 );
	istringstream ss1( coef );
	istringstream ss2( exp );
	ss1 >> c;
	ss2 >> e;

	if ( !( ss1 && ss1.eof() && ss2 && ss2.eof() ) )
		return false;

	if ( str.substr( right + 1 ) == "" )
		return true;
	return isValidPoly( str.substr( right + 1 ) );
}

bool isValidExp( const string &str ) {
	int exp1 = 1 << 30;
	int exp2 = 0;
	int comma = 0;
	int right = str.find( ")" ) ;

	while ( ( comma = str.find( ",", comma + 1 ) ) != string::npos ) {
		right = str.find( ")", comma );
		exp2 = atoi( str.substr( comma + 1, right - comma - 1 ).c_str() );
		if ( exp2 < 0 || exp1 <= exp2 )
			return false;
		exp1 = exp2;
	}

	return true;
}

