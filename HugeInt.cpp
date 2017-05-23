#include<iostream> 
#include<string> 
#include<vector> 
#include<list> 
#include<sstream> 

using namespace std; 

class HugeInt{ 

public: 

	HugeInt(); 

	HugeInt(const HugeInt &x); 

	HugeInt(std::string s); 

	HugeInt(int x); 

	friend std::ostream& operator<<(std::ostream &out, HugeInt x); 

	friend std::istream& operator>>(std::istream &in, HugeInt &x); 

	friend HugeInt operator+(HugeInt l, HugeInt r); 

	friend HugeInt operator-(HugeInt l, HugeInt r); 

	HugeInt& operator=(HugeInt r); 


private: 

	std::vector<int> num; 

	void constructFromString(const std::string &s); 



	static HugeInt& add(HugeInt &l, const HugeInt &r); 
	static HugeInt& sub(HugeInt &l, const HugeInt &r); 
}; 

	HugeInt::HugeInt(){ 
		num.push_back(0); 
	} 

	HugeInt::HugeInt(const HugeInt &x){ 
		num = x.num; 
	} 

	HugeInt::HugeInt(std::string s){ 
		constructFromString(s); 
	} 

	void HugeInt::constructFromString(const std::string &s){ 
		num.clear(); 

		for(int i=s.size()-1;i>=0;--i) 

		num.push_back(s[i]-'0'); 
	} 
	HugeInt::HugeInt(int x){ 
		while(x){ 
			num.push_back(x%10); 
			x /= 10; 
			} 
	} 


	std::ostream& operator<<(std::ostream &out, HugeInt x){ 
		for(int i=x.num.size()-1;i>=0;--i) 
			out << x.num[i]; 
		return out; 
	} 

	std::istream& operator>>(std::istream &in, HugeInt &x){ 
		std::string s; 
		in >> s; 
		x.constructFromString(s); 
		return in; 
	} 
	HugeInt operator+(HugeInt l, HugeInt r){ 
	return HugeInt::add(l, r); 
	} 
	HugeInt operator-(HugeInt l, HugeInt r){ 
	return HugeInt::sub(l, r); 
	} 

	HugeInt& HugeInt::operator=(HugeInt r){ 
		this->num = r.num; 
		return *this; 
	} 

	HugeInt& HugeInt::add(HugeInt &l, const HugeInt &r){ 
		l.num.resize(std::max(l.num.size(), r.num.size())); 
		for(int i=0;i<r.num.size();++i) 
			l.num[i] += r.num[i]; 

		for(int i=1;i<l.num.size();++i){ 
			if(l.num[i-1] >= 10){ 
				l.num[i-1] -= 10; 
				++ l.num[i]; 
			} 
		} 

		if(l.num.back() >= 10){ 
			l.num.back() -= 10; 
			l.num.push_back(1); 
		} 

		return l; 

		} 

	HugeInt& HugeInt::sub(HugeInt &l, const HugeInt &r){ 

		l.num.resize(std::max(l.num.size(), r.num.size())); 

		for(int i=0;i<r.num.size();++i) 

			l.num[i] -= r.num[i]; 

		for(int i=0, end = l.num.size()-1 ; i<end ;++i){ 

			if(l.num[i] < 0){ 
				l.num[i] += 10; 
				-- l.num[i+1]; 
			} 

		} 

		if(l.num.back() == 0){ 
			l.num.pop_back(); 
		} 

		return l; 

		} 
int main(){ 
	HugeInt x; 
	
	HugeInt y(28825252); 

	HugeInt z("314159265358979323846"); 

	HugeInt result; 

	cin >> x; 

	result = x+y; 

	cout << x << "+" << y << " = " << result << endl; 

	result = z - x; 

	cout << result << endl; 

	return 0; 
	}
