#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//variables:    vector<int> alturas;
//		vector<int> anchos;
//		int maximo;
//		int altura_ultimo_edificio;

//int maxAscendente(vector<int> altura, vector<int> ancho, int altura_ultimo_edificio, int i){
//	if(i == altura.size()){return 0;}
//	if(altura[i] > altura_ultimo_edificio){
//		return max(maxAscendente(altura, ancho, altura[i], i+1) + ancho[i],maxAscendente(altura, ancho, altura_ultimo_edificio, i+1));
//	}
//	if(altura[i] < altura_ultimo_edificio){
//		return maxAscendente(altura, ancho, altura_ultimo_edificio, i+1);
//	}
//}

void imprimirVector(vector<int> output){
	cout << "Output: [" << output[0];
	for(int i=1;i<output.size();i++){
		cout << "," << output[i];
	}
	cout << "]" << endl;
}



int maxAscendente(vector<int>& altura, vector<int>& ancho, int altura_ultimo_edificio, int i, vector<int>& max_hasta_i){
	if(i == altura.size()){return 0;}
	if(max_hasta_i[i] == -1){
		
		cout << endl;
		cout << "ALTURA_ULTIMO: " << altura_ultimo_edificio << endl;
		cout << "ALTURA ACTUAL: " << altura[i] << endl;
		
		if(altura[i] > altura_ultimo_edificio){
		
			cout << endl;
			cout << "altura[i] > altura_ultimo_edificio" << endl;
			imprimirVector(max_hasta_i);
		
			max_hasta_i[i] = max(maxAscendente(altura, ancho, altura[i], i+1, max_hasta_i) + ancho[i],maxAscendente(altura, ancho, altura_ultimo_edificio, i+1, max_hasta_i));
		}
		if(altura[i] <= altura_ultimo_edificio){	
		
			cout << endl;
			cout << "altura[i] <= altura_ultimo_edificio" << endl;
			imprimirVector(max_hasta_i);
		
			max_hasta_i[i] = maxAscendente(altura, ancho, altura_ultimo_edificio, i+1, max_hasta_i);
		}
		
		cout << endl;
		imprimirVector(max_hasta_i);
		
		return max_hasta_i[i];
	} else {
		cout << endl;
		cout << "YA ESTA DEFINIDO.." << i << endl;
		cout << "maximo hasta i: " << max_hasta_i[i] << endl;
		imprimirVector(max_hasta_i);
		return max_hasta_i[i];
	}
}


int maxDescendente(vector<int>& altura, vector<int>& ancho, int altura_ultimo_edificio, int i, vector<int>& max_hasta_i){
	if(i < 0){return 0;}
	if(max_hasta_i[i] == -1){
		if(altura[i] > altura_ultimo_edificio){
			max_hasta_i[i] = max(maxDescendente(altura, ancho, altura[i], i-1, max_hasta_i) + ancho[i],maxDescendente(altura, ancho, altura_ultimo_edificio, i-1, max_hasta_i));
		}
		if(altura[i] <= altura_ultimo_edificio){	
			max_hasta_i[i] = maxDescendente(altura, ancho, altura_ultimo_edificio, i-1, max_hasta_i);
		}
		return max_hasta_i[i];
	} else {
		return max_hasta_i[i];
	}
}



int main(){
	int cant_test;
	cin >> cant_test;
	for(int i=1;i<=cant_test;i++){
		int cant_edificios;
		cin >> cant_edificios;
		vector<int> altura(cant_edificios);
		vector<int> ancho(cant_edificios);
		for(int j=0; j<cant_edificios;j++){
			cin >> altura[j];
		}
		for(int j=0; j<cant_edificios;j++){
			cin >> ancho[j];
		}

		//veo el maximo ascendente
		vector<int> max_hasta_i_A(altura.size(), -1);
		int maxA = maxAscendente(altura, ancho, 0, 0, max_hasta_i_A);

		//veo el maximo descendente
		vector<int> max_hasta_i_D(altura.size(), -1);
		int maxD = maxDescendente(altura, ancho, 0, cant_edificios-1, max_hasta_i_D);

		if(maxA >= maxD){
			cout << "Case " << i << ". " << "Increasing (" << maxA << "). ";
			cout << "Decreasing (" << maxD << ")." << endl;
		} else {
			cout << "Case " << i << ". " << "Decreasing (" << maxD << "). ";
			cout << "Increasing (" << maxA << ")." << endl;
		}
	}
}






