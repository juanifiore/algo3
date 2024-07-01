#include <iostream>
using namespace std;

int main(){
	int n;
	while(true){
		cin >>n;
		cout << "leido: " << n << endl;
		if(cin.eof()) break;
	}
}

