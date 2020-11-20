#pragma once
#include<stdexcept>
typedef class CFraction
{
private:
	typedef long long type;
	type numerator;//分子
	type denominator;//分母
	static type GCD(type x, type y);
	static type LCM(type x, type y);
public:
	CFraction();
	CFraction(type, type)throw();
	CFraction(const CFraction&);
	CFraction(long double)throw();
	type GetNumerator()const;
	type GetDenominator()const;
	long double GetFractionalValue()const;
	void SetNumerator(type);
	void SetDenominator(type)throw();
	void Assign(type, type)throw();
	void Assign(long double)throw();
	void Assign(const CFraction&);
	void ReductionOfTheFraction();//约分
	void ReductionOfTheFractionToACommonDenominator(CFraction&);//通分
	CFraction Reciprocal();//倒数
	type Compare(CFraction)const;
	CFraction operator=(const CFraction&);
	bool operator==(CFraction)const;
	bool operator!=(CFraction)const;
	bool operator>(CFraction)const;
	bool operator<(CFraction) const;
	bool operator>=(CFraction) const;
	bool operator<=(CFraction) const;
	CFraction operator+(CFraction)const;
	CFraction operator-(CFraction)const;
	CFraction operator*(CFraction)const;
	CFraction operator/(CFraction)const;
	CFraction operator+=(const CFraction&);
	CFraction operator-=(const CFraction&);
	CFraction operator*=(const CFraction&);
	CFraction operator/=(const CFraction&);
	bool IsIrreducibleFraction()const;//是否为最简分数
	bool CanItBeAFiniteDecimal()const;//能否化成有限小数
}分数;

