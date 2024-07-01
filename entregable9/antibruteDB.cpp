#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <tuple>
#include <list>

using namespace std;

void print(priority_queue<tuple<int,int>,vector<tuple<int,int>>,greater<tuple<int,int>>> priorityQueue){
  while (!priorityQueue.empty()){
    // Each element of the priority
    // queue is a tuple itself
    tuple<int, int> Tuple = priorityQueue.top();

    cout << "[ ";

    cout << get<0>(Tuple) << ' ' << get<1>(Tuple);
    cout << ']';
    cout << '\n';

    // Pop out the topmost tuple
    priorityQueue.pop();
  }
}

void printGrafo(vector<priority_queue<tuple<int,int>,vector<tuple<int,int>>,greater<tuple<int,int>>>> grafo, int n){
	for(int i=0;i<n;i++){
		cout << "LISTA ADY " << i << endl;
		print(grafo[i]);
		cout << endl;
	}
}

void printList(const list<int>& lista) {
    cout << "Lista: ";
    for (const auto& elemento : lista) {
        cout << elemento << " ";
    }
    cout << endl;
}

int peso(int n, int m){
	vector<int> ni = {(n/1000)%10,(n/100)%10,(n/10)%10,n%10};
	vector<int> mi = {(m/1000)%10,(m/100)%10,(m/10)%10,m%10};
	int peso = 0;
	for(int j=0;j<4;j++){
		int p = abs(ni[j]-mi[j]);
		if(p > 5){
			p = 10-p;
		}
		peso+=p;
	}
	return peso;
}
	

int clave_mas_cercana_a_0000(vector<int> keys, int n){
	int p;
	int peso_minimo = 21;
	int min_i;
	for(int i=0;i<n;i++){
		p = peso(0000,keys[i]);
		if(p < peso_minimo){
			peso_minimo = p;
			min_i = i;
		}
	}
	return min_i;
}

		
int min_rolls(vector<priority_queue<tuple<int,int>,vector<tuple<int,int>>,greater<tuple<int,int>>>>& grafo, const vector<int>& keys, int inicio,int n){
	int peso_total = 0;
	list<int> pisados;
	vector<int> nodo_pisado(n,0);
	pisados.push_back(inicio);
	nodo_pisado[inicio] = 1;
	peso_total += peso(0000,keys[inicio]);
	cout << peso_total << endl;
	printList(pisados);
	while(pisados.size() < n){
		int peso_minimo = 25; //el peso no puede exceder de 20
		//indice del nodo de origen de la arista con menor peso actual
		int nodo_origen;

		//indice del nodo de llegada de la arista con menor peso actual
		int nodo_llegada;

		printList(pisados);
		cout << endl;

		for(auto it = pisados.begin(); it != pisados.end();){
			//chequeo entre los nodos ya pisados cual es la arista que tiene menor peso
			int nodo = *it;
			if(grafo[nodo].empty()){ //si ya agregue todas las aristas de ese nodo lo omito
				it++;
			} else {
				if(get<0>(grafo[nodo].top()) < peso_minimo){ //si el peso de la arista mas liviana es menor que la actual hago reemplazos
					if(nodo_pisado[get<1>(grafo[nodo].top())] == 1){ // si esa arista dirije a un nodo visitado la omito pero no itero
						grafo[nodo].pop();
					} else {
					peso_minimo = get<0>(grafo[nodo].top()); //reemplazo el peso minimo actual por el de la arista
					nodo_origen = nodo; //guardo el indice del nodo de donde sale la arista
					nodo_llegada = get<1>(grafo[nodo].top()); //guardo el indice del nodo de llegada de la arista
					it++;
					}
				}
			}
		}
		grafo[nodo_origen].pop(); // elimino la arista ganadora del heap de aristas del nodo origen 
		peso_total += peso_minimo; // sumo el peso de esa arista
		pisados.push_back(nodo_llegada); // agrego el nodo de llegada a los pisados (en la proxima iteracion lo voy a iterar)
		nodo_pisado[nodo_llegada] = 1; //agrego el nodo a la lista de pisados

		cout << "GRAFO " << n << ": " << endl;
		printGrafo(grafo, n);
		cout << endl;
		cout << peso_total << endl;
		cout << endl;

	}
	return peso_total;
}


int main(){
	int t;
	cin >>t;
	while(t>0){
		int n;
		cin >>n;
		vector<int> keys(n);
		int k;
		for(int i=0;i<n;i++){
			cin >> k;
			keys[i] = k;
		}
		
		//lista de adyacencias, con min heap para los pesos de las aristas
		vector<priority_queue<tuple<int,int>,vector<tuple<int,int>>,greater<tuple<int,int>>>> grafo(n);


		//creo el grafo implementado como lista de adyacencias, usando minheaps
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(i!=j){
					int p = peso(keys[i],keys[j]);
					grafo[i].push(make_tuple(p,j));
				}
			}
		}

		cout << "GRAFO INICIAL: " << endl;
		printGrafo(grafo, n);
		cout << endl;

		int inicio = clave_mas_cercana_a_0000(keys, n);
		cout << "INICIO: " << inicio << endl;

		int peso = min_rolls(grafo, keys, inicio, n);
		
		cout << peso << endl;

		t--;
	}
}

		
				


