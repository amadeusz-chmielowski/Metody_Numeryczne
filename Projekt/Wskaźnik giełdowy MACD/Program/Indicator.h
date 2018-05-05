#pragma once
#include <vector>
using namespace std;

class Indicator {
private:
	vector<double> wig20;
	vector<double> MACD;
	vector<double> SIGNAL;
	vector<int> bought_sold;
	struct Wallet {
		double budget;
		double stock;
	}wallet;
public:
	void calculateSignalMACD();
	void firstStrategy();
	void secondStrategy();
	void thirdStrategy();
	void print();

	Indicator();
};
