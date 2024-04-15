#include <iostream>
#include <vector>

using namespace std;

void imprimirVector(vector<int>& out){
	cout << "[" << out[0];
	for(int i=1;i<out.size();i++){
		cout << "," << out[i];
	}
	cout << "]" << endl;
}

void imprimirMatriz(vector<vector<int>>& out){
	for(int i=0;i<out.size();i++){
		imprimirVector(out[i]);
	}
}

void bottom_up(int arbolActual, int alturaActual, const int& salto, vector<vector<int>>& beyotas, vector<int>& maxEnAlturaH){
	cout << "ARBOL ACTUAL: " << arbolActual << endl;
	cout << "ALTURA ACTUAL: " << alturaActual << endl;
	cout << endl;
	if(alturaActual == 0){
		if(beyotas[arbolActual][0] > maxEnAlturaH[0]){
		       	maxEnAlturaH[0] = beyotas[arbolActual][0];
		}
	} else if (alturaActual<salto){
		beyotas[arbolActual][alturaActual] += beyotas[arbolActual][alturaActual-1];
		if(beyotas[arbolActual][alturaActual] > maxEnAlturaH[alturaActual]){
			maxEnAlturaH[alturaActual] = beyotas[arbolActual][alturaActual];
		}
	} else {
		if(maxEnAlturaH[alturaActual-2] > beyotas[arbolActual][alturaActual-1]){
			beyotas[arbolActual][alturaActual] += maxEnAlturaH[alturaActual-salto];
		} else {
			beyotas[arbolActual][alturaActual] += beyotas[arbolActual][alturaActual-1];
		}
		if(beyotas[arbolActual][alturaActual] > maxEnAlturaH[alturaActual]){
			maxEnAlturaH[alturaActual] = beyotas[arbolActual][alturaActual];
		}
	}
	cout << "MAXIMOS:" << endl;
	imprimirVector(maxEnAlturaH);
	cout << endl;
	imprimirMatriz(beyotas);
	cout << endl;
}


int main(){
	int cantidad_test;
	cin >> cantidad_test;
	for(int i=0;i<cantidad_test;i++){
		
		int cantidadArboles;
		int altura;
		int salto;
		cin >>cantidadArboles>>altura>>salto;
		int maximaCantidadDeBeyotasQuePuedeAgarrarJayJay;
		vector<int> maxEnAlturaH(altura,0);
		vector<vector<int>> beyotas(cantidadArboles, vector<int> (altura,0));

		cout << "cantidadarboles " << cantidadArboles<< endl;
		cout << "altura " << altura << endl;
		cout << "salto " << salto << endl;


		int cantidadBeyotas;
		int alturaDeBeyota;
		for(int n=0;n<cantidadArboles;n++){
			cin >> cantidadBeyotas;
			for(int b=0;b<cantidadBeyotas;b++){
				cin >> alturaDeBeyota;
				beyotas[n][alturaDeBeyota-1]++;
			}
		}

		if(i==cantidad_test-1){
				
		cout << "MATRIZ INICIAL" << endl;
		imprimirMatriz(beyotas);
		
		for(int altura_i=0;altura_i<altura;altura_i++){
			for(int arbol_j=0;arbol_j<cantidadArboles;arbol_j++){
				bottom_up(arbol_j, altura_i, salto, beyotas, maxEnAlturaH);
			}
		}

		maximaCantidadDeBeyotasQuePuedeAgarrarJayJay = maxEnAlturaH[altura-1];

		cout << maximaCantidadDeBeyotasQuePuedeAgarrarJayJay << endl;
		}

	}
}


