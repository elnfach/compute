#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;
double exact = 0.180256169819054;

double func(double x) {
	double ans = cos(3 * x) - pow(x, 3);
	return ans;
}
double LeftRect(double* X, int n, double h) {
	double sum = 0, ans, l;
	for (int i = 0; i < n; i++) {
		sum += func(X[i]);
	}
	ans = h * sum;
	l = abs(ans - exact);
	cout << "Метод левых прямоугольников" << endl;
	cout << "Погрешность = " << l << endl;
	return ans;
}
double RightRect(double* X, int n, double h) {
	double sum = 0, ans, l;
	for (int i = 1; i <= n; i++) {
		sum += func(X[i]);
	}
	ans = h * sum;
	l = abs(ans - exact);
	cout << "Метод правых прямоугольников" << endl;
	cout << "Погрешность = " << l << endl;
	return ans;
}
double MiddleRect(double* X, int n, double h) {
	double sum = 0, ans, Xsr, l;
	for (int i = 1; i <= n; i++) {
		Xsr = (X[i - 1] + X[i]) / 2;
		sum += func(Xsr);
	}
	ans = h * sum;
	l = abs(ans - exact);
	cout << "Метод средних прямоугольников" << endl;
	cout << "Погрешность = " << l << endl;
	return ans;
}
double Trap(double* X, int n, double h) {
	double sum = 0, ans, l;
	for (int i = 1; i < n; i++) {
		sum += func(X[i]);
	}
	ans = h * ((func(X[0]) + func(X[n])) / 2 + sum);
	l = abs(ans - exact);
	cout << "Метод трапеции" << endl;
	cout << "Погрешность = " << l << endl;
	return ans;
}
double Simpson(double* X, int n, double h) {
	double sum = 0, ans, even = 0, uneven = 0, l;
	for (int i = 1; i < n; i++) {
		if (i % 2 == 0) even += func(X[i]);
		else uneven += func(X[i]);
	}
	ans = (h / 3) * (func(X[0]) + func(X[n]) + (4 * uneven) + (2 * even));
	l = abs(ans - exact);
	cout << "Метод Симсона" << endl;
	cout << "Погрешность = " << l << endl;
	return ans;
}

#ifdef NUMERICAL_INTEGRATION

int main() {
	setlocale(LC_ALL, "Ru");
	int n, i, p;
	double a, b, h;
	bool chk = true;
	char c;
	cout.setf(ios_base::fixed);
	cout << "Введите отрезок [a,b]" << endl;
	cin >> a >> b;
	cout << "Введите кол-во разбиений n" << endl;
	cin >> n;
	h = (b - a) / n;
	double* X = new double[n + 1];
	X[0] = a;
	X[n] = b;
	for (i = 1; i <= n; i++) {
		X[i] = X[i - 1] + h;
	}
	while (chk) {
		cout << endl;
		cout << "Выберите метод решения:" << endl << "1. Метод левых прямоугольников" << endl;
		cout << "2. Метод правых прямоугольников" << endl << "3. Метод средних прямоугольников" << endl;
		cout << "4. Метод трапеций" << endl << "5. Метод Симпсона" << endl << "6. Выход" << endl;
		cin >> p;
		cout << endl;
		switch (p) {
		case 1:
			cout << "Ответ: " << LeftRect(X, n, h) << endl;
			break;
		case 2:
			cout << "Ответ: " << RightRect(X, n, h) << endl;
			break;
		case 3:
			cout << "Ответ: " << MiddleRect(X, n, h) << endl;
			break;
		case 4:
			cout << "Ответ: " << Trap(X, n, h) << endl;
			break;
		case 5:
			cout << "Ответ: " << setprecision(15) << Simpson(X, n, h) << endl;
			break;
		case 6:
			chk = false;
			break;
		default:
			cout << "Ошибка" << endl;
			break;
		}
		cout << "Завершить? y/n" << endl;
		cin >> c;
		if (c == 'y') chk = false;
	}
	return 0;
}

#endif // NUMERICAL_INTEGRATION