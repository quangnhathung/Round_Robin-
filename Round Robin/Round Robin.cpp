//Quang Nhat Hung
#include<iostream>
#include<queue>
#include<iomanip>
#include<cstdlib>
#include<string.h>
using namespace std;

struct process {
	string name;//tên 
	int ExecutionTime;//tg thực hiện
	int TimeCome;//tg den
	int Waitngtime;//tg chờ 
	int Turnaround;//tg hoàn thành
	int remainnig;//tg còn lại
};
queue<process> wait;
//Mang luu ket qua
queue<process> temp;
process a[20];
process c[20];
int z = 0;
void Add(int n) {
	int i = 0;
	while (i < n) {
		process a;
		cout << "Nhap tien trinh thu " << i + 1 << endl;
		a.name = "P0";
		a.name[1] += i + 1;
	cout << "\tThoi gian den:"; cin >> a.TimeCome;
		cout << "\tThoi gian thuc hien:"; cin >> a.ExecutionTime;
		a.remainnig = a.ExecutionTime;
		a.Waitngtime = 0 - a.TimeCome;
		a.Turnaround = 0;
		c[i] = a;
		i++;
	}
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (c[j].TimeCome < c[i].TimeCome) {
				process temp = c[i];
				c[i] = c[j];
				c[j] = temp;
			}
		}
	}
	i = 0;
	while (i < n) {
		temp.push(c[i]);
		i++;
	}
}
int timeprocess = 0;
void RR(int q, int n) {
	wait.push(c[0]);
	temp.pop();
	while (!wait.empty()) {
		process x = wait.front();
		wait.pop();
		if (x.remainnig - q > 0) {
			x.remainnig -= q;
			timeprocess += q;
		}
		else {
			timeprocess += x.remainnig;
			x.Waitngtime += timeprocess - x.ExecutionTime;
			x.remainnig -= q;
			x.Turnaround = timeprocess - x.TimeCome;
			a[z] = x;
			z++;
			continue;
		}
		while (!temp.empty()){
			if (temp.front().TimeCome < timeprocess) {
				wait.push(temp.front());
				temp.pop();
			}
			else break;
		}
		wait.push(x);
	}
}
process b[20];
void Sort(int n) {//sap xep laij mang a theo thoi gian tu be den lon
	for (int i = 0; i < n; i++) {
		b[i] = a[i];
	}
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (b[j].TimeCome < b[i].TimeCome) {
				process temp = b[i];
				b[i] = b[j];
				b[j] = temp;
			}
		}
	}
}
void Ketqua(int n) {
	cout << "*************************************" << endl;
	cout << setw(13) << left << "Tien trinh" << setw(10) << left << "T/g cho" << setw(15) << left << "T/g hoan thanh" << left << endl;
	cout << "*************************************" << endl;
	for (int i = 0; i < n; i++) {
		cout << setw(5) << right << b[i].name << setw(12) << b[i].Waitngtime << setw(13) << b[i].Turnaround << endl;

	}
	cout << "\nThoi gian cho trung binh la: ";
	int s = 0;
	int i = 0;
	while (i < n) {
		s += b[i].Waitngtime;
		i++;
	}
	cout << 1.00 * s / n;
	return;
}
int main() {
	int q;
	cout << "Muon bao nhieu tien trinh: ";
	int n; cin >> n;
	Add(n);
	cout << endl << "Quantumn time: "; cin >> q;
	RR(q,n);
	Sort(n);
	system("cls");
	cout << "\t\tKet qua:\n";
	Ketqua(n);
	return 0;
}