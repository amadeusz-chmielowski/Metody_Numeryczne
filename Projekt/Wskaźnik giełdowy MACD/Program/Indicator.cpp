#include "Indicator.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>

double EMA(int actualSample, int period, vector<double> data) {
	double nominator = 0, denominator = 0, one_minus_alpha;
	one_minus_alpha = 1 - (2 / (period - 1));
	for (int j = 0; j <= period; j++) {
		if (actualSample - j < 0) continue;
		nominator += data[actualSample - j] * pow(one_minus_alpha, j);
		denominator += pow(one_minus_alpha, j);
	}
	return nominator / denominator;
}
void Indicator::calculateSignalMACD() {
	//ifstream dataSamples("data/Wig20.txt");
	ifstream dataSamples("data/wig20_1000probek.txt");


	double sample;
	while (dataSamples >> sample) {
		wig20.push_back(sample);
	}

	for (int i = 0; i < 1000; i++) {
		//EMA_12
		double EMA_12 = EMA(i, 12, wig20);
		//EMA_26
		double EMA_26 = EMA(i, 26, wig20);

		MACD.push_back(EMA_12 - EMA_26);

		//SIGNAL
		double EMA_9 = EMA(i, 9, MACD);

		SIGNAL.push_back(EMA_9);
	}


	//------ZAPIS DO PLIKOW------//
	ofstream macdData("data/MACD.txt");
	ofstream signalData("data/Signal.txt");
	for (auto var : MACD) {
		macdData << var << endl;
	}
	for (auto var : SIGNAL) {
		signalData << var << endl;
	}
}
void Indicator::print() {
	cout.precision(10);
	double startingFunds = wig20[0] * 1000;
	double finalFunds = wallet.budget + wallet.stock*wig20[999];
	cout << "Starting funds: " << startingFunds << "$." << endl;
	cout << "Your budget left: " << wallet.budget << "$." << endl;
	cout << "Your stock has " << wallet.stock << " more to spend." << endl;
	cout << "Your wallet is worth " << finalFunds << "$ now." << endl;
	cout << "You earned " << finalFunds - startingFunds << "$, which means your profit equals "
		<< (float)((finalFunds - startingFunds) / startingFunds * 100) << "%.\n\n" << endl;

	wallet.budget = 0.0;
	//wallet.stock = 1000.0;
	wallet.stock = 1000000 / wig20[0];
	bought_sold.clear();
}
void Indicator::firstStrategy() {
	cout << "The first strategy: 'NOTHING STRATEGY'.\n" << endl;
	print();
}
void Indicator::secondStrategy() {
	cout << "The second strategy: 'ALL FOR ALL'.\n" << endl;

	for (int i = 37; i < 1000; i++) {
		if (MACD[i - 2] <= SIGNAL[i - 2] && MACD[i - 1] >= SIGNAL[i - 1]) {
			wallet.stock += wallet.budget / wig20[i];
			wallet.budget = 0;
			bought_sold.push_back(200);
		}
		else if (MACD[i - 2] >= SIGNAL[i - 2] && MACD[i - 1] <= SIGNAL[i - 1]) {
			wallet.budget += wallet.stock * wig20[i];
			wallet.stock = 0;
			bought_sold.push_back(-200);

		}
		else {
			bought_sold.push_back(0);
		}

	}
	ofstream bs("data/bought_sold_2.txt");
	for (auto var : bought_sold) {
		bs << var << endl;
	}
	print();
}
void Indicator::thirdStrategy() {
	cout << "The third strategy: 'Filter'.\n" << endl;
	double MACDBuyLevel = -40;
	double MACDSellLevel = 10;
	enum pos {
		LONG,
		SHORT,
		NONE
	}position;
	position = NONE;
	for (int i = 2; i < 998; i++) {
		if (position == NONE) {
			if (MACD[i - 1] < 0 && MACD[i - 2]<SIGNAL[i - 2] && MACD[i-1]>SIGNAL[i-1])  //PIERWSZY SYGNA£ KUPNA
				if (MACD[i-1] < MACDBuyLevel)  //PIERWSZY FILTR
				if (MACD[i - 1] > MACD[i - 2]) { //DRUGI FILTR
					position = LONG;//OTWIERAMY POZYCJE DLUGA
				}

			if (MACD[i - 1] > 0 && MACD[i - 2] > SIGNAL[i - 2] && MACD[i - 1] < SIGNAL[i - 1])  //PIERWSZY SYGNA£ SPRZEDA¯Y
				if (MACD[i - 1] > MACDSellLevel)  //PIERWSZY FILTR
					if (MACD[i-1] < MACD[i - 2]) { //DRUGI FILTR
						position = SHORT;//OTWIERAMY POZYCJE KROTKA
					}

		}
		else {
			if (MACD[i - 1] > 0 && MACD[i - 2] > SIGNAL[i - 2] && MACD[i - 1] < SIGNAL[i - 1]) {  //SYGNA£ DO ZAMKNIECIA POZYCJI DLUGIEJ
				position == NONE;
			}

			if (MACD[i - 1] < 0 && MACD[i - 2]<SIGNAL[i - 2] && MACD[i - 1]>SIGNAL[i - 1]) {  //SYGNA£ DO ZAMKNIECIA POZYCJI KROTKIEJ
				position == NONE;
			}
		}

		if (position == LONG) {
			if (wallet.budget >= 100 * wig20[i+2]) {
				wallet.budget -= 100 * wig20[i + 2];
				wallet.stock += 100;
				bought_sold.push_back(200);
			}
			else
				bought_sold.push_back(0);
			position = NONE;

		}
		else if (position == SHORT) {
			if (wallet.stock >= 100) {
				wallet.budget += 100 * wig20[i + 2];
				wallet.stock -= 100;
				bought_sold.push_back(-200);

			}else
				bought_sold.push_back(0);
			position = NONE;

		}
		else {
			bought_sold.push_back(0);
		}
	}

	ofstream bs("data/bought_sold_3.txt");
	for (auto var : bought_sold) {
		bs << var << endl;
	}
	print();
}
Indicator::Indicator() {
	wallet.budget = 0.0;
	wallet.stock = 1000.0;
	wig20.reserve(1000);
	MACD.reserve(1000);
	SIGNAL.reserve(1000);
	bought_sold.reserve(1000);
}