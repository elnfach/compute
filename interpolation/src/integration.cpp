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
	cout << "����� ����� ���������������" << endl;
	cout << "����������� = " << l << endl;
	return ans;
}
double RightRect(double* X, int n, double h) {
	double sum = 0, ans, l;
	for (int i = 1; i <= n; i++) {
		sum += func(X[i]);
	}
	ans = h * sum;
	l = abs(ans - exact);
	cout << "����� ������ ���������������" << endl;
	cout << "����������� = " << l << endl;
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
	cout << "����� ������� ���������������" << endl;
	cout << "����������� = " << l << endl;
	return ans;
}
double Trap(double* X, int n, double h) {
	double sum = 0, ans, l;
	for (int i = 1; i < n; i++) {
		sum += func(X[i]);
	}
	ans = h * ((func(X[0]) + func(X[n])) / 2 + sum);
	l = abs(ans - exact);
	cout << "����� ��������" << endl;
	cout << "����������� = " << l << endl;
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
	cout << "����� �������" << endl;
	cout << "����������� = " << l << endl;
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
	cout << "������� ������� [a,b]" << endl;
	cin >> a >> b;
	cout << "������� ���-�� ��������� n" << endl;
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
		cout << "�������� ����� �������:" << endl << "1. ����� ����� ���������������" << endl;
		cout << "2. ����� ������ ���������������" << endl << "3. ����� ������� ���������������" << endl;
		cout << "4. ����� ��������" << endl << "5. ����� ��������" << endl << "6. �����" << endl;
		cin >> p;
		cout << endl;
		switch (p) {
		case 1:
			cout << "�����: " << LeftRect(X, n, h) << endl;
			break;
		case 2:
			cout << "�����: " << RightRect(X, n, h) << endl;
			break;
		case 3:
			cout << "�����: " << MiddleRect(X, n, h) << endl;
			break;
		case 4:
			cout << "�����: " << Trap(X, n, h) << endl;
			break;
		case 5:
			cout << "�����: " << setprecision(15) << Simpson(X, n, h) << endl;
			break;
		case 6:
			chk = false;
			break;
		default:
			cout << "������" << endl;
			break;
		}
		cout << "���������? y/n" << endl;
		cin >> c;
		if (c == 'y') chk = false;
	}
	return 0;
}

#endif // NUMERICAL_INTEGRATION