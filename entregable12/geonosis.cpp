#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;


long long int energia_necesaria(vector<vector<int>>& energias_min, vector<int>& orden, int n){
	long long int suma_energia=0;
	list<int> torres_de_pie;
	for(int e=n-1;e>=0;e--){
		int torre_de_pie = orden[e];
		torres_de_pie.push_back(torre_de_pie);
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				energias_min[i][j] = min(energias_min[i][j],energias_min[i][torre_de_pie] + energias_min[torre_de_pie][j]);
			}
		}

		for(auto t : torres_de_pie){
			for(auto u : torres_de_pie){
				if(t != u){
					suma_energia+= energias_min[t][u];
				}
			}
		}
	}
	return suma_energia;
}
			

int main(){
	int c;
	cin >> c;
	while(c>0){
		int n;
		cin >> n;

		// grafo pesado de energias entre las n torres
		vector<vector<int>> energia(n,vector<int>(n,0));
		int e;
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				cin>>e;
				energia[i][j] = e;
			}
		}
		
		// orden en que hay que derribar las torres
		vector<int> orden(n,0);
		for(int i=0;i<n;i++){
			cin >> e;
			orden[i] = e;
		}

		long long int energia_para_derribar_geonosis = energia_necesaria(energia,orden,n);
		
		cout << energia_para_derribar_geonosis << endl;
		c--;
	}
}








