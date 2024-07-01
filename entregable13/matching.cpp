#include <iostream>
#include <string>
#include <climits>
#include <queue>
#include <vector>

using namespace std;

void imprimir_matriz(vector<vector<int>> matriz, int n){
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cout << matriz[i][j] << " ";
		}
		cout << endl;
	}
}

void imprimir_vector(vector<int> vector, int n){
	cout << "[" << vector[0];
	for(int i=1; i<n; i++){
		cout << ", " << vector[i]; 
	}
	cout << "]" << endl;
}
	

bool bfs(vector<vector<int>>& grafo, int s, int t,vector<int>& padre, int V){
	

	vector<bool> pisado(V,false);
	queue<int> cola;
	
	cola.push(s);
	pisado[s] = true;
	padre[s] = -1;	

	bool llegue_a_t = s==t;
	while(!cola.empty() && !llegue_a_t){
		int u = cola.front();
		cola.pop();

		for(int i=0; i<V; i++){
			if(pisado[i] == false && grafo[u][i] > 0){
				padre[i] = u;
				cola.push(i);
				pisado[i] = true;
				if(i == t){
					llegue_a_t = true;
				} 
			}
		}
	}
	return llegue_a_t;
}


int ford_felkurson(vector<vector<int>>& grafo, int s, int t, int V){
	
	vector<int> padre(V,0);
	
	int flujo_maximo = 0;
	bool hay_camino_aumento = false;

	hay_camino_aumento = bfs(grafo,s,t,padre,V);

	while(hay_camino_aumento){

		int residuo_minimo = INT_MAX;
		// primero obtengo el minimo residuo
		for(int v = t; v != s; v = padre[v]){
			int u = padre[v];
			residuo_minimo = min(residuo_minimo,grafo[u][v]);
		}

		// recorro el camino de aumento actualizando el grafo de residuos (que uso el mismo que el original)
		for(int v = t; v != s; v = padre[v]){
			int u = padre[v];
			grafo[u][v] -= residuo_minimo;
			grafo[v][u] += residuo_minimo;
		}
		
		flujo_maximo += residuo_minimo;

		hay_camino_aumento = bfs(grafo,s,t,padre,V);

	}

	return flujo_maximo;
}


int main(){
	int c;
	cin >> c;
	while(c>0){
		c--;

		int n,m;
		cin >>n>>m;

		vector<vector<int>> grafo(m+8,vector<int>(m+8,0));
					//la fuente es el cero
					//las personas van del 1..m
					//los talles van del m+1..m+6
					//el sumidero es el m+7

		vector<string> talles = {"XS","S","M","L","XL","XXL"};

		for(int i=1;i<=m;i++){
			string t1,t2;
			cin >>t1>>t2;
			int ti,tj;
			for(int i=0;i<6;i++){
				if(t1 == talles[i]){ti=i+m+1;}
				if(t2 == talles[i]){tj=i+m+1;}
			}

			// el nodo cero es el 's'
			// las personas tienen indices 1<=i<=m
			grafo[0][i] = 1;

			// a cada persona le asigno el talle, donde cada talle le corresponde un int:
			grafo[i][ti] = 1;
			grafo[i][tj] = 1;
		}
		for(int i=m+1;i<=m+6;i++){
			grafo[i][m+7] = n/6;
		}

		int flujo_maximo = ford_felkurson(grafo, 0, m+7, m+8);


		if(flujo_maximo == m){
			cout << "YES" << endl;
		} else {
			cout << "NO" << endl;
		}
	}
}









