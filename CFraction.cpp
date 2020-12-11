#include "CFraction.h"
CFraction::type CFraction::GCD(type x, type y)
{
	type t;
	while (y != 0)
	{
		t = x % y;
		x = y;
		y = t;
	}
	return x;
}

CFraction::type CFraction::LCM(type x, type y)
{
	return x * y / GCD(x, y);
}

CFraction::CFraction()
{
	numerator = 1;
	denominator = 1;
}

CFraction::CFraction(type n, type d = 1) throw()
{
	Assign(n, d);
}

CFraction::CFraction(const CFraction& fraction)
{
	Assign(fraction);
}

CFraction::CFraction(long double d)throw()
{
	Assign(d);
}

CFraction::type CFraction::GetNumerator()const
{
	return numerator;
}

CFraction::type CFraction::GetDenominator()const
{
	return denominator;
}

long double CFraction::GetFractionalValue() const
{
	return (static_cast<long double>(numerator)/denominator);
}

void CFraction::SetNumerator(type n)
{
	numerator = n;
}

void CFraction::SetDenominator(type d)throw()
{
	if (d == 0)
		throw std::invalid_argument("分母为0！");
	denominator = d;
}

void CFraction::Assign(type n, type d)throw()
{
	if (d == 0)
		throw std::invalid_argument("分母为0！");
	numerator = n;
	denominator = d;
}

void CFraction::Assign(long double d) throw()
{
	if (d == 0)
		throw std::invalid_argument("参数为0！");
	type i = 1;
	while (d - static_cast<long double>(static_cast<type>(d)) > 1e-15)
	{
		d *= 10;
		i *= 10;
	}
	this->numerator = static_cast<type>(d);
	this->denominator = i;
	this->ReductionOfTheFraction();
}

void CFraction::Assign(const CFraction& fraction)
{
	this->numerator = fraction.numerator;
	this->denominator = fraction.denominator;
}

void CFraction::ReductionOfTheFraction()
{
	type i = GCD(numerator, denominator);
	numerator /= i;
	denominator /= i;
}

void CFraction::ReductionOfTheFractionToACommonDenominator(CFraction& fraction)
{
	this->ReductionOfTheFraction();
	fraction.ReductionOfTheFraction();
	type lcm = LCM(this->denominator, fraction.denominator);
	this->numerator *= (lcm / this->denominator);//分母乘几，分子也乘几
	fraction.numerator *= (lcm / fraction.denominator);
	this->denominator = lcm;//分母等于最小公倍数
	fraction.denominator = lcm;
}

CFraction CFraction::operator=(const CFraction& fraction)
{
	Assign(fraction);
	return *this;
}

CFraction CFraction::Reciprocal()
{
	return CFraction(this->denominator,this->numerator);
}

CFraction::type CFraction::Compare(CFraction fraction)const
{
	CFraction t(*this);
	t.ReductionOfTheFractionToACommonDenominator(fraction);
	return (t.numerator - fraction.numerator);
}

bool CFraction::operator==(CFraction fraction) const
{
	return (Compare(fraction) == 0);
}

bool CFraction::operator!=(CFraction fraction) const
{
	return (Compare(fraction) != 0);
}

bool CFraction::operator>(CFraction fraction) const
{
	return (Compare(fraction) > 0);
}

bool CFraction::operator<(CFraction fraction) const
{
	return (Compare(fraction) < 0);
}

bool CFraction::operator>=(CFraction fraction) const
{
	return (Compare(fraction) >= 0);
}

bool CFraction::operator<=(CFraction fraction) const
{
	return (Compare(fraction) <= 0);
}

CFraction CFraction::operator+(CFraction fraction) const
{
	CFraction t(*this);
	t.ReductionOfTheFractionToACommonDenominator(fraction);
	t.numerator += fraction.numerator;
	t.ReductionOfTheFraction();
	return t;
}

CFraction CFraction::operator-(CFraction fraction) const
{
	CFraction t(*this);
	t.ReductionOfTheFractionToACommonDenominator(fraction);
	t.numerator -= fraction.numerator;
	t.ReductionOfTheFraction();
	return t;
}

CFraction CFraction::operator*(CFraction fraction) const
{
	CFraction t(*this);
	t.ReductionOfTheFraction();
	fraction.ReductionOfTheFraction();
	//先约分，防止溢出
	type tmp=t.numerator;
	t.numerator = fraction.numerator;
	fraction.numerator = tmp;
	t.ReductionOfTheFraction();
	fraction.ReductionOfTheFraction();
	/*
	交换分子后再约分，防止溢出。例如，计算(10000000000/10000000001)*(10000000001/10000000000)时
	直接计算会溢出，交换分子后约分变成(1/1)*(1/1)，不会溢出。
	*/
	t.numerator *= fraction.numerator;
	t.denominator *= fraction.denominator;
	return t;//已是最简分数，无需约分
}

CFraction CFraction::operator/(CFraction fraction) const
{
	return operator*(fraction.Reciprocal());//除以一个数等于乘这个数的倒数
}

CFraction CFraction::operator+=(const CFraction& fraction)
{
	Assign(operator+(fraction));
	return *this;
}

CFraction CFraction::operator-=(const CFraction& fraction)
{
	Assign(operator-(fraction));
	return *this;
}

CFraction CFraction::operator*=(const CFraction& fraction)
{
	Assign(operator*(fraction));
	return *this;
}

CFraction CFraction::operator/=(const CFraction& fraction)
{
	Assign(operator/(fraction));
	return *this;
}

bool CFraction::IsIrreducibleFraction() const
{
	return (GCD(numerator, denominator) == 1);
}

bool CFraction::CanItBeAFiniteDecimal() const
{
	CFraction t(*this);
	t.ReductionOfTheFraction();
	while (1)//化成最简分数后判断分母是否只有2和5这两个因数
	{
		if (t.denominator % 2 == 0)
			t.denominator /= 2;
		else if (t.denominator % 5 == 0)
			t.denominator /= 5;
		else
		{
			if (t.denominator == 1)
				return true;
			return false;
		}
	}
}
