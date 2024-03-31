#include <iostream>
#include <vector>
#include <string>

using namespace std;

void ordenar_por_nombre(vector<string>& jugadores, vector<int>& ataque, vector<int>& defensa){
    //cout << "F: ordenar_por_nombre" << endl;
    //uso un insertion sort mirando los nombres de los jugadores pero modifico tambien los vectores que tienen el numero de ataque y defensa
    string j_actual;
    int a_actual;
    int d_actual;
    for(int i=1;i < jugadores.size(); i++){
//       cout << "for " << i << endl;
        j_actual = jugadores[i];
        a_actual = ataque[i];
        d_actual = defensa[i];

        int j = i-1;
        while(j >= 0 && jugadores[j] > j_actual){
//            cout << "while " << j << endl;
            jugadores[j+1] = jugadores[j];
            ataque[j+1] = ataque[j];
            defensa[j+1] = defensa[j];
            j = j-1;
        }
//        cout << "despues del while " << j << endl;
        jugadores[j+1] = j_actual;
        ataque[j+1] = a_actual;
        defensa[j+1] = d_actual;
    }
}

//puntajes seria la lista de ataque o defensa, la lista de indices seria la lista de 5 jugadores candidatos
int sumaDeHabilidad(vector<int> indices, vector<int> puntajes){
//    cout << "F: sumaDeHabilidad" << endl;
    int suma=0;
    for(int i=0; i<indices.size(); i++){
        suma+=puntajes[indices[i]];
    }
    return suma;
}

bool pertenece(int i, vector<int> v){
//    cout << "F: pertenece" << endl;
    bool r = false;
    for(int j=0;j<v.size();j++){
        if(v[j]==i){r=true;}
    }
    return r;
}

//dada una lista de 5 jugadores (que serian los delanteros) obtengo a partir de ellos los indices de los 5 defensores
vector<int> obtenerDefensores(vector<int>& delanteros){
//    cout << "F: obtenerDefensores" << endl;
    vector<int> defensores;
    for(int i=0; i<10; i++){
        if(!pertenece(i,delanteros)){
            defensores.push_back(i);
        }
    }
    return defensores;
}

// para comparar enc aso de que sumen mismo ataque, veo los defensores
bool esMejorDefensa(vector<int>& defensa, vector<int> mejor_ataque_actual, vector<int> mejores_delanteros){
//    cout << "F: esMejorDefensa" << endl;
    vector<int> defensores_actuales = obtenerDefensores(mejor_ataque_actual);
    vector<int> mejores_defensores = obtenerDefensores(mejores_delanteros);
    return sumaDeHabilidad(defensores_actuales, defensa) > sumaDeHabilidad(mejores_defensores, defensa);
}


// al ordenar los jugadores lexicograficamente antes de la recursion, sabemos que en caso de empate, los atacantes que hayamos formado primero van a ser los que tengan prioridad.


void mejor_equipo(vector<string>& jugadores, vector<int>& ataque, vector<int>& defensa, vector<int>& mejor_ataque_actual,vector<int>& mejores_delanteros, int& max_ataque, int& max_actual, int i){
    // la variable i la uso para indexar sobre los jugadores.
    // la variable mejor_ataque_actual posee los indices con los delanteros formados hasta el momento en la recursion. el max_actual es la suma de los ataques de los jugadores actuales.
    if(i>=11){return;}
    if(mejor_ataque_actual.size() == 5){
        cout << "B: mejor_ataque_actual.size() == 5 or i==10" << endl;
        cout << "max_ataque:" << max_ataque << endl;
        cout << "max_actual:" << max_actual << endl;
        cout << "mejor_ataque_actual: " << endl;
        for(int i=0;i<mejor_ataque_actual.size();i++){
            cout << mejor_ataque_actual[i] << endl;
        }
        cout << "mejores_delanteros:" << endl;
        for(int i=0;i<mejores_delanteros.size();i++){
            cout << mejores_delanteros[i] << endl;
        }
        if(max_actual > max_ataque or (max_actual == max_ataque and esMejorDefensa(defensa, mejor_ataque_actual,mejores_delanteros))){
            cout << "B: max_actual > max_ataque or... " << endl;
            cout << "ASIGNACION" << endl;
            cout << "max_ataque:" << max_ataque << endl;
            cout << "max_actual:" << max_actual << endl;
            cout << "mejor_ataque_actual: " << endl;
            for(int i=0;i<mejor_ataque_actual.size();i++){
                cout << mejor_ataque_actual[i] << endl;
            }
            cout << "mejores_delanteros:" << endl;
            for(int i=0;i<mejores_delanteros.size();i++){
                cout << mejores_delanteros[i] << endl;
            }
            cout << endl;
            max_ataque = max_actual;
            mejores_delanteros = mejor_ataque_actual;
        } else { 
            cout << "B: primer else" << endl;
            //return; 
        } 
    } else {
        cout << "B: segundo ELSE" << endl;
        cout << "max_ataque:" << max_ataque << endl;
        cout << "max_actual:" << max_actual << endl;
        cout << "mejor_ataque_actual: " << endl;
        for(int i=0;i<mejor_ataque_actual.size();i++){
            cout << mejor_ataque_actual[i] << endl;
        }
        cout << "mejores_delanteros:" << endl;
        for(int i=0;i<mejores_delanteros.size();i++){
            cout << mejores_delanteros[i] << endl;
        }
        mejor_ataque_actual.push_back(i);
        max_actual = sumaDeHabilidad(mejor_ataque_actual,ataque);
        mejor_equipo(jugadores, ataque, defensa, mejor_ataque_actual, mejores_delanteros, max_ataque, max_actual, i+1);
        mejor_ataque_actual.pop_back();
        max_actual = sumaDeHabilidad(mejor_ataque_actual,ataque);
        mejor_equipo(jugadores, ataque, defensa, mejor_ataque_actual, mejores_delanteros, max_ataque, max_actual, i+1);
    }
}
        
            

int main(){
    int cant_test;
    cin >> cant_test;

    string nombre;
    int ataque;
    int defensa;
    
    vector<string> jugadores(10);
    vector<int> ataque_i(10);
    vector<int> defensa_i(10);

    for(int i=1;i <= cant_test;i++){

        for(int j=0;j<10;j++){
            cin >> nombre >> ataque >> defensa;
            jugadores[j] = nombre;
            ataque_i[j] = ataque;
            defensa_i[j] = defensa;

        }

        for(int i=0; i<jugadores.size();i++){
            cout << jugadores[i] << endl;
            cout << ataque_i[i] << endl;
            cout << defensa_i[i] << endl;
        }

        ordenar_por_nombre(jugadores, ataque_i, defensa_i);

        for(int i=0; i<jugadores.size();i++){
            cout << jugadores[i] << endl;
            cout << ataque_i[i] << endl;
            cout << defensa_i[i] << endl;
        }

        
        vector<int> mejores_delanteros;
        int max_ataque = 0;
        vector<int> mejor_ataque_actual;
        int max_actual = 0;

        mejor_equipo(jugadores, ataque_i, defensa_i, mejor_ataque_actual, mejores_delanteros, max_ataque, max_actual, 0);

        vector<int> mejores_defensores = obtenerDefensores(mejores_delanteros);

        //imprimo la respuesta. formato:
        //Case i:
        //(del1, del2, del3, del4, del5)
        //(def1, def2, def3, def4, def5)

        cout << "Case " << i << ":" << endl;
        //delanteros
        cout << "(" << jugadores[mejores_delanteros[0]];
        for(int i=1; i<mejores_delanteros.size();i++){
            cout << "," << jugadores[mejores_delanteros[i]];
        }
        cout << ")" << endl;
        //defensa
        cout << "(" << jugadores[mejores_defensores[0]];
        for(int i=1; i<mejores_defensores.size();i++){
            cout << "," << jugadores[mejores_defensores[i]];
        }
        cout << ")" << endl;

    }
    return 0;
}



        

        




