#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

int main()
{
	// -> Presetting the parameters of the summation:
	double x = 9.0 / 16.0;
	double coefficient = 1, sum = 0, ordered_sum = 0;
	vector<double> coefficients = { coefficient };
	int n = 0;
	// -> Calculation of all the required coefficients using the Leibniz test.
	while (abs(coefficient) > 1e-12) {
		n++;
		coefficient *= -x * (2 * (double)n) * (2 * (double)n - 1) / (4 * pow((double)n, 2));
		coefficients.push_back(coefficient);
	}
	coefficients.pop_back();
	// -> Calculation of 3 "different" sums using the calculated coefficients.
	for (int i = 0; i < n; i++) { sum += coefficients[i]; }
	double kahan_sum = 0, c = 0;
	for (int i = 0; i < n; i++) {
		double y = coefficients[i] - c;
		volatile double t = kahan_sum + y;
		volatile double z = t - kahan_sum;
		c = z - y;
		kahan_sum = t;
	}
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1 - i; j++) {
			if (coefficients[j] > coefficients[j + 1]) {
				double placeholder = coefficients[j];
				coefficients[j] = coefficients[j + 1];
				coefficients[j + 1] = placeholder;
			}
		}
	}
	// -> Output of the results.
	for (int i = 0; i < n; i++) { ordered_sum += coefficients[i]; }
	double value = 0.8;
	cout << setprecision(16) << left;
	cout << "x:  " << x << ",    n:  " << n << '.' << endl;
	cout << setw(24) << "f(x) = (1+x)^(-0.5):  " << value << ';' << endl;
	cout << setw(24) << "sum_1 (naive):  " << sum << setw(15) << ",    delta_1:  " << value - sum << ';' << endl;
	cout << setw(24) << "sum_2 (ordered):  " << ordered_sum << setw(15) << ",    delta_2:  " << value - ordered_sum << ';' << endl;
	cout << setw(24) << "sum_3 (Kahan):  " << kahan_sum << setw(15) << ",    delta_3:  " << value - kahan_sum << '.' << endl;
	return 0;
}