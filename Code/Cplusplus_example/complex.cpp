/*
 * =====================================================================================
 *
 *       Filename:  complex.cpp
 *
 *    Description:   
 *
 *        Version:  1.0
 *        Created:  10/07/2022 06:31:49 PM
 *       Revision:  none
 *       Compiler:  gcc/clang
 *
 *         Author:  YangYuPeng, Yongy2022@outlook.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>

using namespace std;

class complex
{
    double re, im;	// 实部和虚部
public:
    complex(double r, double i): re{r}, im{i}{}
    complex(double r): re{r}, im{0}{}
    complex():re{0}, im{0}{}

    double real() const{ return re; }
    void real(double d) { re = d; }
    double imag() const{ return im; }
    void imag(double d) { im = d; }
    complex& operator+=(complex z) { re += z.re; im += z.im; return *this; }
    complex& operator-=(complex z) { re -= z.re; im -= z.im; return *this; }
    complex& operator*=(complex z) { re = re*z.re - im*z.im; im = re*z.im + im*z.re; return *this; }
    complex& operator/=(complex z) {
	double temp = z.re*z.re + z.im*z.im;
	re = (re*z.re + im*z.im)/temp;
	im = (im*z.re - re*z.im)/temp;
	return *this;
    }

};


complex operator+(complex a, complex b) { return a+=b; }
complex operator-(complex a, complex b) { return a-=b; }
complex operator-(complex a) { return {-a.real(), -a.imag()}; }
complex operator*(complex a, complex b) { return a*=b; }
complex operator/(complex a, complex b) { return a/=b; }

bool operator==(complex a, complex b)
{
    return a.real()==b.real() && a.imag()==b.imag();
}
bool operator!=(complex a, complex b)
{
    return !(a==b);
}

int main()
{
    complex first{2, 3};
    complex second;
    cout << "first.re = " << first.real() << " first.im = " << first.imag() << endl;
    cout << "second.re = " << second.real() << " second.im = " << second.imag() << endl;
    complex third = first + second;
    cout << "third.re = " << third.real() << " third.im = " << third.imag() << endl;
    complex a{2.3};
    complex b{1/a};
    complex c{a+b*complex{1,2.3}};
    cout << "c.re = " << c.real() << " c.im = " << c.imag() << endl;
    if(c != b)
	c = -(b/a)+2*b;
     
    cout << "a.re = " << a.real() << " a.im = " << a.imag() << endl;
    cout << "b.re = " << b.real() << " b.im = " << b.imag() << endl;
    cout << "c.re = " << c.real() << " c.im = " << c.imag() << endl;
}

