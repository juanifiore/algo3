#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <queue>
#include <tuple>
#include <unordered_set>

#define INFINITO 1000000000;

using namespace std;
using pos = tuple<int,int>; //primera posicion: ascensor, segunda: piso
using graph = map<pos,map<pos,int>>;
using conjunto = unordered_set<int>; 
 
map<pos,int> dijkstra(graph grafo, pos inicio, conjunto nodos){
	map<pos,int> distancias; //diccionario de distancias al vertice de inicio que retorna la funcion
	for(it = nodos.begin(), it
				 

	



int main(){
	int n,k;
	while(not cin.fail()){

		cin >>n>>k; //n es cantidad de ascensores, k es el piso al que quiero llegar (n<6, k<101)
		int costos[n]; //costo del ascensor i para pasar de un piso a otro
		int costo;
		
		for(int i=0;i<n;i++){
			cin >> costo;
			costos[i] = costo;
		}
		
		vector<list<int>> pisos(n); //vector de listas, pisos[i] posee la lista de pisos al que llega el elevador i

		string linea; // input de pisos al que llega elevador i

		cin.ignore();	
		for(int i=0;i<n;i++){ //recorro la linea insertando los pisos al vector
			getline(cin,linea);
			int piso = 0;
			for (char d : linea) {
				if (d == ' ') {
				    pisos[i].push_back(piso);
				    piso = 0;
				} else {
				    piso = piso * 10 + (d - '0');
				}
			}
			// me aseguro de insertar el ultimo numero si no hay un espacio al final de la linea
			if (!linea.empty() && linea.back() != ' ') {
			pisos[i].push_back(piso);
			}
		}


		//creo matriz de booleanos de ascensores x pisos
		//cada posicion es true si el ascensor tiene acceso a ese piso
		vector<vector<bool>> acceso(n,vector<bool>(100,false));
		vector<int> cantidad_ascensores_llegan(100,0);

		//variables del grafo y conjunto de vertices 
		graph grafo;
		conjunto nodos; //cada vertice se representa con un numero entero: i*100+p, donde i es el ascensor, p es el piso. como p<100 no hay valores repetidos

		//recorro para cada ascensor, la lista de pisos a las que tengo acceso, y creo el grafo pesado
		
		for(int i=0;i<n;i++){
			int piso_anterior = 0;
			int peso;
			for(auto p : pisos[i]){ // recorro la lista de pisos del ascensor i
				pos nodo1(i,piso_anterior); //clave del vertice origen 
				pos nodo2(i,p); //clave del vertice de llegada 
					
				int clave_nodo = i*100+p;
				nodos.insert(clave_nodo); //agrego el nodo al conjunto de vertices

				// calculo el peso a la posicion actual, va a ser el peso de la arista
				peso = costos[i] * (p-piso_anterior); // peso para llegar del piso anterior al actual
				acceso[i][p] = true; // marco que el ascensor i tiene acceso al piso p
				cantidad_ascensores_llegan[p]++; // sumo 1 a la cantidad de ascensores con acceso al piso p
								 
				grafo[nodo1][nodo2] = peso;//agrego clave-valor al mapeo (grafo)	
				piso_anterior = p; //reemplazo para la proxima iteracion
			}
		}

		//recorro matriz de booleanos donde guarde los accesos a los pisos
		//para cada piso donde mas de un ascensor tenga acceso, agrego esa arista al grafo con peso 60
		for(int p=0;p<100;p++){
			if(cantidad_ascensores_llegan[p] > 1){ // si mas de un ascensor tiene acceso al piso p
				for(int a=0;a<n;a++){
					for(int b=0;b<n;b++){ 
						if(a!=b and acceso[a][p] and acceso[b][p]){ //agrego al grafo las aritas de peso 60
							pos nodo1(a,p);
							pos nodo2(b,p);
							grafo[nodo1][nodo2] = 60;
						}
					}
				}
			}
		}

		//agrego un vertice nodo_0 conectado a los vertices de los ascensores con acceso al piso cero
		// y otro nodo_fin que este conectado a los que tengan ascensores que llegan al piso k
		pos nodo_0(6,0);
		pos nodo_fin(6,k);
		for(it = nodos.begin(); it != nodos.end(); it++){
			if(*it%100 == 0){
				int ascensor = *it/100;
				int piso = *it%100;
				pos nodo(ascensor,piso);
				grafo[nodo_0][nodo] = 0;
			} else if(*it%100 == k){
				int ascensor = *it/100;
				int piso = *it%100;
				pos nodo(ascensor,piso);
				grafo[nodo][nodo_fin] = 0;
			}
		}

		map<pos,int> distancias_minimas = dijkstra(grafo, nodo_0, nodos);


	}
}
				
			

		







			


