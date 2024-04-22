#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void swap(string& s, string& t, int i, int j){
	char s_i = s[i];
	s[i] = t[j];
	t[j] = s_i;
}

vector<int> greedy(string& s, string& t, int n){
	//uso un par de vectores para guardar las posiciones donde no coinciden los caracteres
	//en el primero estan los indices donde en el string s hay una a, y en el string t hay una b. en el segundo vector al reves
	vector<int> swap_a_b;
	vector<int> swap_b_a;
	
	for(int i=0;i<n;i++){ // O(n) dentro del ciclo hay todas operaciones O(1)
		if(s[i] != t[i]){ 
			if(s[i] == 'a'){
				swap_a_b.push_back(i);
			} else {
				swap_b_a.push_back(i);
			}
		}
	}

	int a = swap_a_b.size();
	int b = swap_b_a.size();

	//si la cantidad de caracteres distintos es impar no se pueden igualar los string
	if((a + b) % 2 == 1) return vector<int>();

	int m;
	if(a%2 == 0){
		m = a+b;
	} else {
		m = a+b + 2;
	}

	vector<int> swaps(m,-1);
	int j = 0;

	// recorro los indices y voy swapeando para hacerlos iguales
	for(int i=0;i<a;i+=2){
		if(i+1 < a){
			swap(s,t,swap_a_b[i],swap_a_b[i+1]);
			swaps[i] = swap_a_b[i];
			swaps[i+1] = swap_a_b[i+1];
			j+=2;
		}
	}
	for(int i=0;i<b;i+=2){
		if(i+1 < b){
			swap(s,t,swap_b_a[i],swap_b_a[i+1]);
			swaps[j] = swap_b_a[i];
			swaps[j+1] = swap_b_a[i+1];
			j+=2;
		}
	}

	// si eran impares los vectores hago el ultimo swap doble para igualar las palabras
	if(a % 2 == 1){
		swap(s,t,swap_a_b[a-1],swap_a_b[a-1]);
		swaps[j] = swap_a_b[a-1];
		swaps[j+1] = swap_a_b[a-1];
		swap(s,t,swap_a_b[a-1],swap_b_a[b-1]);
		swaps[j+2] = swap_a_b[a-1];
		swaps[j+3] = swap_b_a[b-1];
	}

	return swaps;

}
	
int main(){
	int n;
	cin >> n;
	string s;
	string t;
	cin >>s>>t;
	cout << s << endl << t << endl;
	vector<int> swaps = greedy(s,t,n);
	if(swaps.size() > 0){
		cout << swaps.size()/2 << endl;
		for(int i=0;i<swaps.size()-1;i+=2){
			cout << swaps[i]+1 << " " << swaps[i+1]+1 << endl;
		}
	} else {
		cout << "-1" << endl;
	}
	cout << s << endl << t << endl;
	return 0;
}

		








			
