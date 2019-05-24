#include <iostream>
#include <fstream>
#include <limits>
#include <cmath>

std::ifstream f("mat.txt");

int tablou[100][100] = { 0 }, i, j, randuri = 0, coloane = 0;
int minRand[100] = { 0 };
int maxColoana[100] = { 0 };
double playerA[100] = { 0 }, playerB[100] = { 0 };
int minimColoana = INT_MAX;
int maximRand = INT_MIN;
int pozRand = 0;
int pozCol = 0;
int OddColoana[100] = { 0 };
int OddRand[100] = { 0 };
int SumaColoana = 0, SumaRand = 0;

void AfisareProbabilitatiPlayerA() {
	std::cout << "\nProbabilitati PlayerA=(";

	for (i = 0; i < randuri; ++i) {
		std::cout << playerA[i];
		if (i < randuri - 1) {
			std::cout << ",";
		}
	}
	std::cout << ")";
}


void AfisareProbabilitatiPlayerB() {
	std::cout << "\nProbabilitati PlayerB=(";

	for (i = 0; i < coloane; ++i) {
		std::cout << playerB[i];
		if (i < coloane - 1) {
			std::cout << ",";
		}
	}
	std::cout << ")";
}

void AfisareMatrice() {
	for (i = 0; i < randuri; ++i) {
		for (j = 0; j < coloane; ++j) {
			std::cout << tablou[i][j] << " ";
		}
		std::cout << "\n";
	}
}


int main() {
	
	f >> randuri >> coloane;
	for (i = 0; i < randuri; ++i) {
		for (j = 0; j < coloane; ++j) {
			f >> tablou[i][j];
		}
	}

	AfisareMatrice();

	for (i = 0; i < randuri; ++i) {
		int minim = INT_MAX;
		for (j = 0; j < coloane; ++j) {
			if (minim > tablou[i][j]) {
				minim = tablou[i][j];
			}
		}
		minRand[i] = minim;
	}

	for (i = 0; i < randuri; ++i) {
		//std::cout << minRand[i] << " ";
		if (maximRand < minRand[i]) {
			maximRand = minRand[i];
		}
	}

	
	for (j = 0; j < coloane; ++j) {
		int maxim = INT_MIN;
		for (i = 0; i < randuri; ++i) {
			if (maxim < tablou[i][j]) {
				maxim = tablou[i][j];
			}
		}
		maxColoana[j] = maxim;
	}

	std::cout << "\n";

	for (i = 0; i < coloane; ++i) {
		//std::cout << maxColoana[i] << " ";
		if (minimColoana > maxColoana[i]) {
			minimColoana = maxColoana[i];
		}
	}

	std::cout << "\n";

	if (minimColoana == maximRand) {
		for (i = 0; i < randuri; ++i) {
			for (j = 0; j < coloane; ++j) {
				if (minimColoana == tablou[i][j]) {
					pozRand = i;
					pozCol = j;
				}
			}
		}
		playerA[pozRand] = 1;
		playerB[pozCol] = 1;

		AfisareProbabilitatiPlayerA();

		AfisareProbabilitatiPlayerB();
	}
	else {
		for (i = 0; i < randuri; ++i) {
			int diff = 0;
			for (j = 0; j < coloane; ++j) {
				diff = abs(tablou[i][j] - diff);
			}
			OddRand[randuri - i - 1] = diff;
		}

		for (j = 0; j < coloane; ++j) {
			int diff = 0;
			for (i = 0; i < randuri; ++i) {
				diff = abs(diff - tablou[i][j]);
			}
			OddColoana[coloane - j - 1] = diff;
		}

		for (i = 0; i < randuri; ++i) {
			std::cout << OddRand[i] << ' ';
			SumaRand += OddRand[i];
		}

		std::cout << '\n';

		for (i = 0; i < coloane; ++i) {
			std::cout << OddColoana[i] << ' ';
			SumaColoana += OddColoana[i];
		}

		for (i = 0; i < randuri; ++i) {
			playerA[i] = OddRand[i] * 1.0 / SumaRand;
		}

		for (i = 0; i < coloane; ++i) {
			playerB[i] = OddColoana[i] * 1.0 / SumaColoana;
		}


		AfisareProbabilitatiPlayerA();

		AfisareProbabilitatiPlayerB();
	}
	f.close();
	return 0;
}