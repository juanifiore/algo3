#include <iostream>
#include <climits>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <queue>
#include <tuple>
#include <unordered_set>
#include <sstream>

#define INFINITO 100000000;

using namespace std;
using pos = tuple<int,int>; //primera posicion: ascensor, segunda: piso
using graph = map<pos,map<pos,int>>;
using conjunto = unordered_set<int>; 

// Función para imprimir un unordered_set<int>
void printUnorderedSet(const unordered_set<int>& unorderedSet) {
    std::cout << "Contenido del unordered_set:" << std::endl;
    for (int element : unorderedSet) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

// Función para imprimir un map<tuple<int,int>, map<tuple<int,int>, int>>
void printNestedMap(const std::map<std::tuple<int, int>, std::map<std::tuple<int, int>, int>>& nestedMap) {
    std::cout << "Contenido del map anidado:" << std::endl;
    for (const auto& outerPair : nestedMap) {
        std::cout << "Clave exterior: (" << std::get<0>(outerPair.first) << ", " << std::get<1>(outerPair.first) << ")" << std::endl;
        for (const auto& innerPair : outerPair.second) {
            std::cout << "  Clave interior: (" << std::get<0>(innerPair.first) << ", " << std::get<1>(innerPair.first) << "), Valor: " << innerPair.second << std::endl;
        }
    }
}

void printMap(const map<tuple<int, int>, int>& myMap) {
    cout << "Elementos del map:" << endl;
    for (const auto& pair : myMap) {
        cout << "Clave: (" << get<0>(pair.first) << "," << get<1>(pair.first) << "), Valor: " << pair.second << endl;
    }
}



int id(pos nodo){
	return get<0>(nodo) *100 + get<1>(nodo);
}

pos pos_id(int id){
	int ascensor = id/100;
	int piso = id%100;
	pos nodo(ascensor,piso);
	return nodo;
}

map<pos,int> dijkstra(graph& grafo, pos& inicio, conjunto& nodos){
	int cantidad_nodos = nodos.size();
	map<pos,int> distancias; //diccionario de distancias al vertice de inicio que retorna la funcion

	for(auto it = nodos.begin(); it != nodos.end(); it++){ // asigno distancia infinito a todos los nodos
		distancias[pos_id(*it)] = INT_MAX; // convierto el id del nodo al tipo pos y lo agrego al dicc de distancias con valor infinito
	}

	for(auto u = grafo[inicio].begin(); u != grafo[inicio].end(); u++){
		distancias[u->first] = u->second;
	}

	
	distancias[inicio] = 0;
	nodos.erase(id(inicio));
	
	cout << "V/S" << endl;
	printUnorderedSet(nodos);
	cout << "DISTANCIAS" << endl;
	printMap(distancias);
	cout <<endl<<endl;

	int iterador=0;
	while(!nodos.empty() and iterador < cantidad_nodos){
		pos nodo_min;
		int distancia_minima = INFINITO;
		for(auto w = nodos.begin(); w != nodos.end(); w++){
			pos nodo_w = pos_id(*w);		 
			if(distancias[pos_id(*w)] < distancia_minima){
				nodo_min = nodo_w;
				distancia_minima = distancias[nodo_w];
			}
		}
		nodos.erase(id(nodo_min));
		
		for(auto u = grafo[nodo_min].begin(); u != grafo[nodo_min].end(); u++){
			int u_id = id(u->first);
			if(nodos.find(u_id) != nodos.end() and distancias[u->first] > distancias[nodo_min] + u->second){
				distancias[u->first] = distancias[nodo_min] + u->second;
			}
		}
		cout << "V/S" << endl;
		printUnorderedSet(nodos);
		cout << "DISTANCIAS" << endl;
		printMap(distancias);
		cout <<endl<<endl;
		iterador++;
	}
	return distancias;
}


int main(){
	string nk;
	int caso = 1;
	while(!getline(cin, nk).fail() && !nk.empty()){
		cout << endl << "TEST CASE: " << caso << ", entrada: " << nk << endl;
		bool alguno_llega_al_piso_k = false;
		bool alguno_llega_al_piso_0 = false;
		int n,k;

		istringstream iss(nk);
		iss >> n >> k;

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
			istringstream iss(linea);
			int piso = 0;
			while(iss >> piso){
				if(piso==0){alguno_llega_al_piso_0=true;}
				if(piso==k){alguno_llega_al_piso_k=true;}
				pisos[i].push_back(piso);
			}
		}

		if(!(alguno_llega_al_piso_0 and alguno_llega_al_piso_k)){
			cout << "IMPOSSIBLE" << endl;
		} else {

		//creo matriz de booleanos de ascensores x pisos
		//cada posicion es true si el ascensor tiene acceso a ese piso
		vector<vector<bool>> acceso(n,vector<bool>(100,false));
		vector<int> cantidad_ascensores_llegan(100,0);

		//variables del grafo y conjunto de vertices 
		graph grafo;
		conjunto nodos; //cada vertice se representa con un numero entero: i*100+p, donde i es el ascensor, p es el piso. como p<100 no hay valores repetidos

		//recorro para cada ascensor, la lista de pisos a las que tengo acceso, y creo el grafo pesado
		
		for(int i=0;i<n;i++){
			int piso_anterior = pisos[i].front();
			int peso;
			if(!pisos[i].empty()){
			cantidad_ascensores_llegan[pisos[i].front()]++;
			acceso[i][pisos[i].front()] = true;
			nodos.insert(i*100+pisos[i].front());
			pisos[i].pop_front();
			}
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
				grafo[nodo2][nodo1] = peso;
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
		for(auto it = nodos.begin(); it != nodos.end(); it++){
			if(*it%100 == 0){
				pos nodo = pos_id(*it);
				grafo[nodo_0][nodo] = 0;
			} else if(*it%100 == k){
				pos nodo = pos_id(*it);
				grafo[nodo][nodo_fin] = 0;
			}
		}
		
		//agrego los nodo_0 y nodo_fin al conjunto de nodos
		nodos.insert(600); nodos.insert(600 + k);

		printUnorderedSet(nodos);
	//	cout << endl;
	//	printNestedMap(grafo);
		
		map<pos,int> distancias_minimas = dijkstra(grafo, nodo_0, nodos);
		if(distancias_minimas[nodo_fin] != INT_MAX){
			cout << distancias_minimas[nodo_fin] << endl;
		}else{
			cout << "IMPOSSIBLE" << endl;
		}
		}
		caso++;

	}
}
				

