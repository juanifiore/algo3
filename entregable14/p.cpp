#include <iostream>
#include <vector>
#include <map>

using namespace std;

#define for2(i,j,n,m) for(int i=0;i<n;i++) for(int j=0;j<m;j++)
#define for1(i,k,n) for(int i=k;i<n;i++)

void printmap(const map<int, int>& myMap) {
    for (const auto& pair : myMap) {
        cout << "hijo: " << pair.first << ", padre: " << pair.second << endl;
    }
}

int main(){
	map<int,int> m;
	m[0] = 0;
	m[1] = 1;
	m[2] = 2;
	m[1] = 800;
	m[1] = (m[1]<1000) ? 1500 : m[1];
	printmap(m);
}




