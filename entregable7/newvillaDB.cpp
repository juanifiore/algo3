#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <list>
#include <map>

using namespace std;
using estado = tuple<int,vector<bool>>;

// Función para imprimir un vector de enteros
void printVector(const vector<bool>& vec) {
    cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i];
        if (i < vec.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]";
}

// Función para imprimir un estado
void printEstado(const estado& est) {
    cout << "(" << get<0>(est) << ", ";
    printVector(get<1>(est));
    cout << ")";
}

// Función para imprimir un map<estado, estado>
void printMap(const map<estado, estado>& myMap) {
    for (const auto& pair : myMap) {
        printEstado(pair.first);
        cout << " : ";
        printEstado(pair.second);
        cout << endl;
    }
}

bool puedo_moverme(estado actual, int room,const vector<vector<int>>& rooms){
	//chequeo en el grafo rooms que haya arista entre habitaciones y que este la luz prendida de la habitacion a la que quiero ir
	return rooms[get<0>(actual)][room] and get<1>(actual)[room];
}

bool se_prendio(vector<bool> actuales, vector<bool> anteriores){
	bool rta = false;
	for(int r=0;r<actuales.size();r++){
		if(actuales[r] != anteriores[r]){
			if(actuales[r]){
				rta = true;
			}
		}
	}
	return rta;
}


int indice_luz_modificada(vector<bool> actuales, vector<bool> anteriores){
	int room = -1;
	for(int r=0;r<actuales.size();r++){
		if(actuales[r] != anteriores[r]){
			room = r;
		}
	}
	return room;
}


list<string> camino(map<estado,estado>& arbol, estado inicio, estado llegada, int& cantidad_pasos){
	list<string> pasos;
	estado actual = llegada;
	bool seguir = true;
	while(seguir){
		cantidad_pasos++;
		estado anterior = arbol[actual];
		if(get<0>(actual) != get<0>(anterior)){
			string paso = "- Move to room " + to_string(get<0>(actual)+1) + ".";
			pasos.push_front(paso);
		} else {
			int luz_distinta = indice_luz_modificada(get<1>(actual), get<1>(anterior));
			if(se_prendio(get<1>(actual), get<1>(anterior))){
				string paso = "- Switch on light in room " + to_string(luz_distinta+1) + ".";
				pasos.push_front(paso);
			} else {
				string paso = "- Switch off light in room " + to_string(luz_distinta+1) + ".";
				pasos.push_front(paso);
			}
		}
		if(arbol[actual]==inicio){
			seguir=false;
		}
		actual = anterior;
	}
	return pasos;
}


map<estado,estado> bfsEstados(const vector<vector<int>>& rooms, const vector<vector<int>>& switchs, int r,const estado& inicio,const estado& llegada){
	map<estado, estado> padre;
	list<estado> cola;

	padre[inicio] = inicio;
	cola.push_back(inicio);

	//int contador=0;

	while(!cola.empty()){
		//contador++;
		//cout << endl << "Iteracion " << contador << endl;
		//printMap(padre);

		estado actual = cola.front();
		for(int room=0;room<r;room++){
			if(puedo_moverme(actual, room, rooms)){
				estado siguiente(room, get<1>(actual));
			        if(padre.find(siguiente) == padre.end()){
					padre[siguiente] = actual;
					cola.push_back(siguiente);
				}
			}
		}
		for(int luz=0;luz<r;luz++){
			if(luz != get<0>(actual) and switchs[get<0>(actual)][luz]){
				vector<bool> luces_mod = get<1>(actual);
				luces_mod[luz] = !get<1>(actual)[luz];
				estado siguiente(get<0>(actual),luces_mod);
				if(padre.find(siguiente) == padre.end()){
					padre[siguiente] = actual;
					cola.push_back(siguiente);
				}
			}
		}
		if(actual==llegada){break;}
		cola.pop_front();
	}

	return padre;
}
			


int main(){
	int r; int d; int s;
	cin >>r>>d>>s;
	int contador=0;
	while(r!=0 or d!=0 or s!=0){
		contador++;
		cout << "Villa #" + to_string(contador) << endl;

		// grafo de conexiones entre habitaciones usando matriz ady
		vector<vector<int>> rooms(r,vector<int>(r,0));
		int i; int j;
		for(int n=0;n<d;n++){
			cin >>i>>j;
			rooms[i-1][j-1] = 1;
			rooms[j-1][i-1] = 1;
		}
		// grafo de interruptores de luces usando matriz ady
		vector<vector<int>> switchs(r,vector<int>(r,0));
		int k; int l;
		for(int n=0;n<s;n++){
			cin >>k>>l;
			switchs[k-1][l-1] = 1;
		}

		//defino los estados de inicio y llegada
		vector<bool> luces_inicio(r,false);
		vector<bool> luces_final(r,false);
		luces_inicio[0] = true;
		luces_final[r-1] = true;
		estado inicio(0,luces_inicio);
		estado llegada(r-1,luces_final);


		map<estado,estado> arbol = bfsEstados(rooms, switchs, r, inicio, llegada);

		if(r==1){
			cout << "The problem can be solved in 0 steps:" << endl;
		} else if(arbol.find(llegada) != arbol.end()){
			int cantidad_pasos = 0;
			list<string> pasos = camino(arbol, inicio, llegada, cantidad_pasos);
			cout << "The problem can be solved in " + to_string(cantidad_pasos) + " steps:" << endl;
			while(!pasos.empty()){
				string paso = pasos.front();
				cout << paso << endl;
				pasos.pop_front();
			}
		} else { 
			cout << "The problem cannot be solved." << endl;
		}
		cout << endl;

		cin >>r>>d>>s;

	}
}
