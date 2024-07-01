#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <sstream>
#include <unordered_set>

#define for1(i,k,n) for(int i=k;i<n;i++)

using namespace std;

bool bfs(map<int,map<int,int>>& grafo, int s, int t,map<int,int>& padre){

	unordered_set<int> pisados;
	queue<int> cola;
	
	cola.push(s);
	pisados.insert(s);
	padre[s] = -1;	

	bool llegue_a_t = s==t;
	while(!cola.empty() && !llegue_a_t){
		int u = cola.front();
		cola.pop();

		//for (auto nodo = grafo[u].begin(); nodo != grafo[u].end(); ++nodo)
		for(auto& nodo : grafo[u]){
			if(pisados.find(nodo.first) == pisados.end() && nodo.second > 0){
				padre[nodo.first] = u;
				cola.push(nodo.first);
				pisados.insert(nodo.first);
				if(nodo.first == t){
					llegue_a_t = true;
				} 
			}
		}
	}
	return llegue_a_t;
}


int ford_felkurson(map<int,map<int,int>>& grafo, int s, int t){
	
	map<int,int> padre;
	
	int flujo_maximo = 0;
	bool hay_camino_aumento = false;

	hay_camino_aumento = bfs(grafo,s,t,padre);

	while(hay_camino_aumento){

		int residuo_minimo = 100000;
		// primero obtengo el minimo residuo
		for(int v = t; v != s; v = padre[v]){
			int u = padre[v];
			residuo_minimo = min(residuo_minimo,grafo[u][v]);
		}

		// recorro el camino de aumento actualizando el grafo de residuos (que uso el mismo que el original)
		for(int v = t; v != s; v = padre[v]){
			int u = padre[v];
			if(grafo.find(u) != grafo.end() and grafo[u].find(v) != grafo[u].end()){
				grafo[u][v] -= residuo_minimo;
			} else {
				grafo[v][u] += residuo_minimo;
			}
		}
		
		flujo_maximo += residuo_minimo;

		hay_camino_aumento = bfs(grafo,s,t,padre);

	}
	return flujo_maximo;
}

int main(){

	int x,y,p;
	while(cin >> x >> y >> p){

		int cantidad_max_personas = x*y/2;

		vector<vector<char>> mapa(x,vector<char>(y));

		char obj;
		for1(i,0,x){
			for1(j,0,y){
				cin >> obj;
				mapa[i][j] = obj;
			}
		}

		map<int,map<int,int>> grafo;

		// recorro el mapa y hago un grafo de de las conexiones
		// indico los pesos entre objetos (capacidades)
		// agrego dos que corresponden a la fuente y el sumidero con indices [x*y*2] y [x*y*2+1] respectivamente
		// los nodos estan duplicados, el nodo original es el que recibe el flujo  sus adyacentes desde sus duplicados
		// el nodo original dirige su flujo a su duplicado con capacidad dependiendo del caracter
		// desde ese nodo duplicado se dirige el flujo a los originales de sus adyacentes con capacidad = cantidad_max_personas
		for1(i,0,x){
			for1(j,0,y){
				// asigno aristas con capacidad = cantidad_max_personas, 
				// que van desde un nodo duplicado (se le suma x*y al indice),
				// a los originales de sus adyacentes
				if(i>0){
					grafo[y*(x+i)+j][(i-1)*y+j] = cantidad_max_personas;
				}
				if(i<x-1){
					grafo[y*(x+i)+j][(i+1)*y+j] = cantidad_max_personas;
				}
				if(j>0){
					grafo[y*(x+i)+j][i*y+j-1] = cantidad_max_personas;
				}
				if(j<y-1){
					grafo[y*(x+i)+j][i*y+j+1] = cantidad_max_personas;
				}

				// asigno aristas con capacidad correspondiente al caracter,
				// desde los nodos originales a sus duplicados
				// (y de la fuente a las personas, y de los troncos al sumidero)
				obj = mapa[i][j];
					
				if(mapa[i][j] == '.'){
					grafo[i*y + j][i*y + j + x*y] = 1; // iceberg que se hunde, solo pasa una persona
				}
				//if(mapa[i][j] == '~'){
				//	grafo[i*y + j][i*y + j + x*y] = 0; // por el mar no pasa nadie porque se muere
				//}
				if(mapa[i][j] == '@'){
					grafo[i*y + j][i*y + j + x*y] = cantidad_max_personas; // el iceberg grande se la banca 
				}
				if(mapa[i][j] == '*'){
					grafo[i*y + j][i*y + j + x*y] = 1; // por una persona pasa solo una, o ella misma o otra pero la mata
					grafo[x*y*2][i*y + j] = 1; // conecto la fuente a los nodos originales de las personas
				}
				if(mapa[i][j] == '#'){
					grafo[i*y + j][i*y + j + x*y] = cantidad_max_personas; // el tronco se la banca
					grafo[i*y + j + y*x][2*x*y+1] = p; // conecto los troncos al sumidero, con 
									   // capacidad p (las personas que aguantan los troncos)
				}
			}
		}
		int cantidad_personas_salvadas = ford_felkurson(grafo, 2*x*y, 2*x*y+1);
		cout << cantidad_personas_salvadas << endl;

	}
}
	
