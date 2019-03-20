#pragma once

inline double factorial(int m){
	double res = 1;
	while(m>1){
		res *= m;
		m--;
	}
	return res;
}

inline double combination(const int n, const int i){
	return factorial(n)/(factorial(i)*factorial(n-i));
}
