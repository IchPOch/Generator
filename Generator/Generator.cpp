#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <iostream>
#include <conio.h>
#include <time.h>
#include <random>
#include <map>
#define m time(NULL)
static unsigned x;
using namespace std;
static struct seed_t
{
	unsigned x = 532623232;
	unsigned y = 42342317;
	unsigned z = 32344231;
	unsigned w = 42314231;
};
class Randoms {
private:
	unsigned x = 53262322;
	unsigned y = 42342317;
	unsigned z = 32344231;
	unsigned w = 42314231;
	int seed; 
	vector <unsigned> fibtTenNumber;
	unsigned fibM = 2147483647;
	unsigned curr;

	int k = 10; // largest "-index"
	int j = 7; // other "-index"
public:
	Randoms() {
		seed = time(NULL);
		for (int i = 0; i < 10; ++i) {
			unsigned rand = XorShift128();
			fibtTenNumber.emplace_back(rand);
		}
	}
	//void setdeffvalue() {
	//	static seed_t s;
	//	s.x =  532623232;
	//	s.y = 42342317;
	//	s.z = 32344231;
	//	s.w = 42314231;
	//}
	unsigned XorShift128()
	{
		static seed_t s;
		unsigned t = x ^ (x << 11);
		x = y;
		y = z;
		z = w;
		w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
		return w;
		
	}

	unsigned gen() {
		unsigned z = (x += seed);
		z = (z ^ (z >> 30)) * 7823423084723947;
		z = (z ^ (z << 27)) * 8971624981240812974;
		return z ^ (z >> 31);
	}

	unsigned fibonachi()
	{
		int left = fibtTenNumber[0] % fibM;    // [x-big]
		int right = fibtTenNumber[k - j] % fibM; // [x-other]
		long sum = (long)left + (long)right;

		curr = (int)(sum % fibM);

		fibtTenNumber.emplace_back(curr);
		fibtTenNumber.erase(fibtTenNumber.begin());
		// anew val at end
		return (1.0 * curr) / m;
	}
};
class Tests {
public:
	//Tests(Randoms ran) {
	//	this->ran = ran;
	//}
	void testUnic(int N, Randoms ran) {
		map<unsigned,unsigned> XOR;
		map<unsigned, unsigned> GEN;
		map<unsigned, unsigned> FIB;
		map<unsigned, unsigned> SRA;
		int XORCH = 0;
		int GENCH = 0;
		int FIBCH = 0;
		int SRACH = 0;
		unsigned x;
		for (int i = 0; i < N; i++) {
			x = ran.XorShift128();
			if (XOR.count(x == 1)) XORCH++;
			else {
				XOR.insert(pair<unsigned, unsigned>(x,1));
			}
			x = ran.gen();
			if (GEN.count(x == 1)) GENCH++;
			else {
				GEN.insert(pair<unsigned, unsigned>(x, 1));
			}
			x = ran.fibonachi();
			if (FIB.count(x == 1)) FIBCH++;
			else {
				FIB.insert(pair<unsigned, unsigned>(x, 1));
			}
			srand(time(NULL));
			x = rand();
			if (SRA.count(x == 1)) SRACH++;
			else {
				SRA.insert(pair<unsigned, unsigned>(x, 1));
			}
		}
		cout << "Procent Ne unic chisel v XOR = " << XORCH << endl;
		cout << "Procent Ne unic chisel v GEN = " << GENCH << endl;
		cout << "Procent Ne unic chisel v fibonachi = " << FIBCH << endl;
		cout << "Procent Ne unic chisel v bibliotech = " << SRACH << endl;

	}
	void test2Unic(int N, Randoms ran) {
		Randoms ran2;
		unsigned* XoR1 = new unsigned[N];
		unsigned* XoR2 = new unsigned[N];
		int XORCH = 0;
		int GENCH = 0;
		int FIBCH = 0;
		int SRACH = 0;

		//for (int i = 0; i < N; i++) {
		//	
		//	XoR1[i] = ran.XorShift128();
		//}


		for (int i = 0; i < N; i++) {
			XoR1[i] = ran.XorShift128();
			XoR2[i] = ran2.XorShift128();
			if (XoR1[i] == XoR2[i])XORCH++;
			/*if (ran.XorShift128() == ran2.XorShift128())XORCH++;*/
			if (ran.gen() == ran2.gen())GENCH++;
			if (ran.fibonachi() == ran2.fibonachi())FIBCH++;
			if (rand() == rand())SRACH++;
			//cout << XoR1[i] << "   " << XoR2[i] << endl;
		}
		cout << "unic zapuska razn object v XOR = " << XORCH  << endl;
		cout << "unic zapuska razn object v GEN = " << GENCH  << endl;
		cout << "unic zapuska razn object v fibonachi = " << FIBCH << endl;
		cout << "unic zapuska razn object v bibliotech = " << SRACH  << endl;
	}
	void disperc(int N, Randoms ran) {
		Randoms ran2;
		unsigned* XoR1 = new unsigned[N];
		unsigned* XoR2 = new unsigned[N];
		unsigned* GeN1 = new unsigned[N];
		unsigned* GeN2 = new unsigned[N];
		unsigned* FiB1 = new unsigned[N];
		unsigned* FiB2 = new unsigned[N];
		unsigned* SrA1 = new unsigned[N];
		unsigned* SrA2 = new unsigned[N];
		double XORCH = 0;
		double GENCH = 0;
		double FIBCH = 0;
		double SRACH = 0;

		//for (int i = 0; i < N; i++) {
		//	
		//	XoR1[i] = ran.XorShift128();
		//}

		for (int i = 0; i < N; i++) {
			srand(time(NULL));
			XoR1[i] = ran.XorShift128();
			XoR2[i] = ran2.XorShift128();
			GeN1[i] = ran.gen();
			GeN2[i] = ran2.gen();
			FiB1[i] = ran.fibonachi();
			FiB2[i] = ran2.fibonachi();
			SrA1[i] = rand();
			SrA2[i] = rand();
			XORCH += (fabs((long)XoR1[i] - (long)XoR2[i])) / XoR1[i] * 100;
			GENCH += (fabs((long)GeN1[i] - (long)GeN2[i])) / GeN1[i] * 100;
			FIBCH += (fabs((long)FiB1[i] - (long)FiB2[i])) / FiB1[i] * 100;
			SRACH += (fabs((long)SrA1[i] - (long)SrA2[i])) / SrA1[i] * 100;
		}
		cout << "procent dispers v XOR = " << XORCH / N << endl;
		cout << "procent dispers v GEN = " << GENCH / N << endl;
		cout << "procent dispers v fibonachi = " << FIBCH / N << endl;
		cout << "procent dispers v bibliotech = " << SRACH / N << endl;
	}
	void twotest(int N, Randoms ran) {
		int XORCH = 0;
		int GENCH = 0;
		int FIBCH = 0;
		int SRACH = 0;
		int x;
		srand(time(NULL));
		for (int i = 0; i < N; i++) {

			x = 1 + rand() % 2;
			if (1 + ran.XorShift128() % 2 == 1)XORCH++;
			if (1 + ran.gen() % 2 == 1)GENCH++;
			if (1 + ran.fibonachi() % 2 == 1)FIBCH++;
			if (x == 1)SRACH++;
		}
		cout << "Kolvo 1 iz vseh chisel u XOR = " << XORCH << endl;
		cout << "Kolvo 1 iz vseh chisel u GEN = " << GENCH << endl;
		cout << "Kolvo 1 iz vseh chisel u fibonachi = " << FIBCH << endl;
		cout << "Kolvo 1 iz vseh chisel u bibliotech = " << SRACH << endl;
	}
};


int main()
{
	srand(time(NULL));
	Randoms ran;
	int N;
	cin >> N;
	cout << endl;
	Tests test;
	test.testUnic(N, ran);
	cout << endl;
	test.test2Unic(N,ran);
	cout << endl;
	test.disperc(N, ran);
	cout << endl;
	test.twotest(N,ran);

}

