#include<iostream>
#include<iomanip>
#include"CFraction.h"
using namespace std;
void ShowFraction(CFraction f,string name,int i=15)//i为输出精度
{
	cout << name << '=' << f.GetNumerator() << '/' << f.GetDenominator() << '\t'
		<< "分数值=" << setprecision(i) << f.GetFractionalValue() << endl;

}

int main()
{
	try {
		CFraction f1(15,75);
		ShowFraction(f1, "分数1");
		f1.ReductionOfTheFraction();
		ShowFraction(f1, "约分后，分数1");
		ShowFraction(f1 / CFraction(1, 3), "(分数1)/(1/3)");
		if (f1 < 0.25)
			cout << "分数1<0.25" << endl;
		f1.Assign(10000000000, 10000000001);
		ShowFraction(f1* CFraction(10000000001, 10000000000), 
			"(10000000000/10000000001)*(10000000001/10000000000)");
	}
	catch(invalid_argument except){
		cout << "出现参数无效异常！异常信息：" << except.what();
	}
	catch(...){
		cout << "出现其它类型异常！"<<endl;
	}
	system("pause");
	return 0;
}