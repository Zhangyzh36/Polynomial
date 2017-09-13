#include <iostream>
#include <vector>
#include <conio.h>
#include <sstream>
#include "Polynomial.h"
using namespace std;

//多项式容器 
vector<Polynomial> record;
//需求类型 
enum RequestType { QUIT = '0', INPUT, ADD, SUBTRACT, MULTI, DIFF, VALUE, ISEQUALTO, SHOW, };

//用户输入，格式为： 多项式名称=(系数，指数)(系数，指数)...(系数，指数)。其中指数为自然数并且降幂输入,输入不含空格。 
void input();
//多项式运算，含加、减、乘 
void operation( char oper );
//多项式求导 
void diff();
//多项式求值 
void value();
//展示所有多项式 
void show();
//输出提示信息 
void help();
//输出输入多项式的提示信息及样例 
void example();
//判断两个多项式是否相等 
void isEqualTo();
//input的子函数 
bool getPolynomial();
//获取操作数
Polynomial getOperand( int i );
//保存输入的多项式 
void save( const string &name, const string &poly );
//保存运算结果 
bool saveNew( Polynomial newPoly );
//在容器中按名字搜索多项式，返回下标 
int findPoly( const string &name );
//判断输入是否合法，例如p=(5,6)(-4,3)(2,0)合法 
bool isValidWithName( const string &str );
//判断多项式序偶组是否合法，例如 (5,6)(-4,3)(2,0)合法 
bool isValidPoly( const string &str );
//判断多项式序偶组是否是降幂输入，例如(2,3)(2,4)不合法 
bool isValidExp( const string &str );

int main() {
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << 
			"                                               欢迎使用多项式计算器!" << endl;
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n" << 
			"                                                                                                  -----请按回车到主菜单" << endl; 
	
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
				cout << "\n感谢使用多项式计算器！" << endl;
				return 0;
				break;

			case 13:
				system( "cls" );
				break;

			default :
				system( "cls" );
				cout << "\n无此选项，请重新输入!" << endl;
				cout << "*********************" << endl;
				break;
		}
	}
	return 0;
}

void help() {
	cout << "\n请输入下列数字来实现：" << endl;
	cout << "[1] 输入多项式" << endl;
	cout << "[2] 多项式加法" << endl;
	cout << "[3] 多项式减法" << endl;
	cout << "[4] 多项式乘法" << endl;
	cout << "[5] 多项式求导" << endl;
	cout << "[6] 多项式求值" << endl;
	cout << "[7] 判断多项式是否相等" << endl;
	cout << "[8] 显示所有多项式" << endl;
	cout << "[0] 退出" << endl;
}

void show() {
	system( "cls" );
	if ( record.empty() )
		cout << "无\n\n按回车返回主菜单";
	else {
		cout << "以下为所有多项式：" << endl;
		for ( int i = 0; i < record.size(); ++i )
			cout << record[ i ] << endl;
		cout <<  "\n按回车返回主菜单";
	}
	while ( getch() != 13 );
	system( "cls" );
}

void example() {
	cout << "\n请输入多项式,格式为：" << endl;
	cout << "\n多项式名称=(系数，指数)(系数，指数)...(系数，指数) " << endl;
	cout << "(指数为自然数并且降幂输入,输入不含空格）" << endl;
	cout << "\n例如：p=(5,6)(-4,3)(2,0)即表示p=5x^6-4x^3+2" << endl;
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
	cout << "请输入多项式";
	if ( i ) cout << i;
	cout << "(名称或新的多项式，输入0返回主菜单)：";
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
			cout << "不存在此多项式或输入格式有误\n" << endl;
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
	cout << "是否保存结果？\n[1] 是\n[2] 不是。\n请输入：";

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
				cout << "请输入此多项式的名字(输入0返回主菜单)：";
				string name;
				cin >> name;
				getchar();
				if ( name ==  "0" ) return false;
				while ( findPoly( name ) != -1 ) {
					cout << "对不起，名字\"" << name << "\"" << "已存在，请重新输入多项式的名字： ";
					cin >> name;
					getchar();
					if ( name ==  "0" ) return false;
				}
				res.setName( name );
				record.push_back( res );
				cout << "保存成功。\n" << endl;
				return true;
			}

			default:
				cout << "无此选项，请重新输入：";
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
		cout << "请输入多项式(名称或新的多项式，输入0返回主菜单)：";
		string poly;
		getline( cin, poly );
		if ( poly == "0" ) {
			system( "cls" );
			break;
		}

		if ( isValidPoly( poly ) && isValidExp( poly ) ) {

			Polynomial temp( poly );
			double num;
			cout << "请输入一个数(输入0退回主菜单)：";
			cin >> num;
			getchar();
			if ( num == 0 ) {
				system( "cls" );
				break;
			}
			cout << "x=" << num << "时，" << temp << "=" << temp.valueOfPolynomial( num ) << endl << endl;
		} else {
			int index = findPoly( poly );
			if ( index == -1 )
				cout << "不存在此多项式或输入格式有误\n" << endl;
			else {
				double num;
				cout << "请输入一个数(输入0退回主菜单)：";
				cin >> num;
				getchar();
				if ( num == 0 ) {
					system( "cls" );
					break;
				}
				cout << "x=" << num << "时，" << poly << "(" << num << ")" << "=" << record[ index ].valueOfPolynomial( num ) << endl << endl;
			}

		}

	}
	return;
}

bool getPolynomial() {
	string polynomialWithName;
	cout << "\n多项式(输入0返回主菜单): ";

	getline( cin, polynomialWithName );
	if ( polynomialWithName == "0" ) {
		system( "cls" );
		return false;
	}

	while ( !isValidWithName( polynomialWithName ) ) {
		cout << "输入格式错误!请重新输入多项式(输入0返回主菜单): ";
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
		cout << "对不起，名字\"" << name << "\"" << "已存在，请重新输入多项式的名字： ";
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

