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
	int Start, End;
};
queue<process> wait;
//Mang luu ket qua
queue<process> temp;
process a[20];
process c[20];
queue<process> grantt;//luu trang thai tien trinh de ve
queue<process> granttTemp;
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
	grantt.push(temp.front());
	temp.pop();
	while (!wait.empty()) {
		process x = wait.front();
		wait.pop();
		if (x.remainnig - q > 0) {
			grantt.front().Start = timeprocess;
			x.remainnig -= q;
			timeprocess += q;
			grantt.front().End = timeprocess;
			granttTemp.push(grantt.front());
			grantt.pop();
		}
		else {
			grantt.front().Start = timeprocess;
			timeprocess += x.remainnig;
			grantt.front().End = timeprocess;
			granttTemp.push(grantt.front());
			grantt.pop();
			x.Waitngtime += timeprocess - x.ExecutionTime;
			x.remainnig -= q;
			x.Turnaround = timeprocess - x.TimeCome;
			a[z] = x;
			z++;
			continue;
		}
		while (!temp.empty()) {
			if (temp.front().TimeCome < timeprocess) {
				wait.push(temp.front());
				grantt.push(temp.front());
				temp.pop();
			}
			else break;
		}
		wait.push(x);
		grantt.push(x);
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
//vẽ sơ đồ grantt
void Draw() {
	cout << endl << "So do Grantt:" << endl;
	int i = 0;
	queue<process> grantt1;
	cout << endl; i = 0;
	int count = 0;
	while (!granttTemp.empty()) {
		cout << setw(2) << left <<"   "<< granttTemp.front().name;
		grantt1.push(granttTemp.front());
		granttTemp.pop();
		count++;
	}
	cout << endl;
	cout << "|";
	i = 0;
	while (i < count) {
		cout << "----|";
		i++;
	}
	cout << endl;
	cout << grantt1.front().Start;
	while (!grantt1.empty()) {
		if (grantt1.front().End < 10) {
			cout << "    " << grantt1.front().End;
		}
		else cout << "   " << grantt1.front().End;
		grantt1.pop();
		count++;
	}
	cout<<endl;
}
void Ketqua(int n) {
	cout << "***************************************************************" << endl;
	cout << setw(13) << left << "Tien trinh";
	cout << setw(10) << left << "T/g den";
	cout << setw(15) << left << "T/g thuc hien";
	cout << setw(10) << left << "T/g cho";
	cout<< setw(15) << left << "T/g hoan thanh" << left << endl;
	cout << "***************************************************************" << endl;
	for (int i = 0; i < n; i++) {
		cout << setw(5) << right << b[i].name;
		cout << setw(12) << right << b[i].TimeCome;
		cout << setw(13) << right << b[i].ExecutionTime;
		cout << setw(12) << b[i].Waitngtime;
		cout<< setw(13) << b[i].Turnaround << endl;

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
	cout << "\t\t\tKet qua:\n";
	Ketqua(n);
	/*while (!granttTemp.empty()) {
		cout << granttTemp.front().name << "  start: " <<granttTemp.front().Start<<" end: "<< granttTemp.front().End << endl;
		granttTemp.pop();
	}*/
	cout << endl;
	Draw();
	return 0;
}