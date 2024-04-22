#include <iostream>
#include <cmath>

using namespace std;

int main(){
	int vecinos;
	cin >> vecinos;
	while(vecinos != 0){
		long long int trabajo=0;
		long long int demanda_acumulada = 0;
		while(vecinos>0){
			int n;
			cin >> n;
			demanda_acumulada+= n;
			trabajo+= abs(demanda_acumulada);
			vecinos--;
		}
		cout << trabajo << endl;
		cin >> vecinos;
	}
	return 0;
}

