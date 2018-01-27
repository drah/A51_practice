#include <bitset>
#include <string>

#define L1H 18
#define L1CB 10
#define L1TB1 5
#define L1TB2 2
#define L1TB3 1
#define L1TB4 0
#define L1T 0
#define L2H 21
#define L2CB 11
#define L2TB1 1
#define L2TB2 0
#define L2T 0
#define L3H 22
#define L3CB 12
#define L3TB1 15
#define L3TB2 2
#define L3TB3 1
#define L3TB4 0
#define L3T 0

using namespace std;

struct myA51{
	bitset<19> L1;
	bitset<22> L2;
	bitset<23> L3;
};

void* A51Initial(unsigned long long sessionKey,unsigned int frameCounter){
	myA51* A51=new myA51;
	bitset<1> keybit;
	bitset<1> inbit;
	for(int i=0;i<64;i++){
		if(sessionKey%2==1)keybit.set();
		else keybit.reset();
		sessionKey>>=1;

		inbit[0]=A51->L1[L1TB1]^A51->L1[L1TB2]^A51->L1[L1TB3]^A51->L1[L1TB4]^keybit[0];
		A51->L1>>=1;
		A51->L1[L1H]=inbit[0];

		inbit[0]=A51->L2[L2TB1]^A51->L2[L2TB2]^keybit[0];
		A51->L2>>=1;
		A51->L2[L2H]=inbit[0];

		inbit[0]=A51->L3[L3TB1]^A51->L3[L3TB2]^A51->L3[L3TB3]^A51->L3[L3TB4]^keybit[0];
		A51->L3>>=1;
		A51->L3[L3H]=inbit[0];
	}
	for(int i=0;i<22;i++){
		if(frameCounter%2==1)keybit.set();
		else keybit.reset();
		frameCounter>>=1;

		inbit[0]=A51->L1[L1TB1]^A51->L1[L1TB2]^A51->L1[L1TB3]^A51->L1[L1TB4]^keybit[0];
		A51->L1>>=1;
		A51->L1[L1H]=inbit[0];

		inbit[0]=A51->L2[L2TB1]^A51->L2[L2TB2]^keybit[0];
		A51->L2>>=1;
		A51->L2[L2H]=inbit[0];

		inbit[0]=A51->L3[L3TB1]^A51->L3[L3TB2]^A51->L3[L3TB3]^A51->L3[L3TB4]^keybit[0];
		A51->L3>>=1;
		A51->L3[L3H]=inbit[0];
	}
	for(int i=0;i<100;i++){
		int L1go,L2go,L3go;
		if(A51->L1[L1CB]==A51->L2[L2CB] || A51->L1[L1CB]==A51->L3[L3CB])L1go=1;
		else L1go=0;
		if(A51->L2[L2CB]==A51->L1[L1CB] || A51->L2[L2CB]==A51->L3[L3CB])L2go=1;
		else L2go=0;
		if(A51->L3[L3CB]==A51->L1[L1CB] || A51->L3[L3CB]==A51->L2[L2CB])L3go=1;
		else L3go=0;
		if(L1go){
			inbit[0]=A51->L1[L1TB1]^A51->L1[L1TB2]^A51->L1[L1TB3]^A51->L1[L1TB4];
			A51->L1>>=1;
			A51->L1[L1H]=inbit[0];
		}
		if(L2go){
			inbit[0]=A51->L2[L2TB1]^A51->L2[L2TB2];
			A51->L2>>=1;
			A51->L2[L2H]=inbit[0];
		}
		if(L3go){
			inbit[0]=A51->L3[L3TB1]^A51->L3[L3TB2]^A51->L3[L3TB3]^A51->L3[L3TB4];
			A51->L3>>=1;
			A51->L3[L3H]=inbit[0];
		}
	}
	return (void *)A51;
}
 
unsigned char A51GetByte(void* LFSR){
	myA51 *A51=(myA51 *)LFSR;
	bitset<8> keystr;
	bitset<1> inbit;
	for(int i=7;i>=0;i--){
		keystr[i]=A51->L1[L1T]^A51->L2[L2T]^A51->L3[L3T];
		int L1go,L2go,L3go;
		if(A51->L1[L1CB]==A51->L2[L2CB] || A51->L1[L1CB]==A51->L3[L3CB])L1go=1;
		else L1go=0;
		if(A51->L2[L2CB]==A51->L1[L1CB] || A51->L2[L2CB]==A51->L3[L3CB])L2go=1;
		else L2go=0;
		if(A51->L3[L3CB]==A51->L1[L1CB] || A51->L3[L3CB]==A51->L2[L2CB])L3go=1;
		else L3go=0;
		if(L1go){
			inbit[0]=A51->L1[L1TB1]^A51->L1[L1TB2]^A51->L1[L1TB3]^A51->L1[L1TB4];
			A51->L1>>=1;
			A51->L1[L1H]=inbit[0];
		}
		if(L2go){
			inbit[0]=A51->L2[L2TB1]^A51->L2[L2TB2];
			A51->L2>>=1;
			A51->L2[L2H]=inbit[0];
		}
		if(L3go){
			inbit[0]=A51->L3[L3TB1]^A51->L3[L3TB2]^A51->L3[L3TB3]^A51->L3[L3TB4];
			A51->L3>>=1;
			A51->L3[L3H]=inbit[0];
		}
	}
	return keystr.to_ulong();
}
