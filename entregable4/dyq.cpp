#include <iostream> 
#include <string>

using namespace std;

bool equivalentes(string p1, string p2, int l){
	if(l % 2 != 0){
		return p1 == p2;
	} else {
		string p11 = p1.substr(0,l/2);
		string p12 = p1.substr(l/2,l/2);
		string p21 = p2.substr(0,l/2);
		string p22 = p2.substr(l/2,l/2);

		return (equivalentes(p11,p21,l/2) && equivalentes(p12,p22,l/2)) || (equivalentes(p12,p21,l/2) && equivalentes(p11,p22,l/2));

	}
}

int main(){
	string p1;
	string p2;
	cin>>p1>>p2;

	bool res = (p1.size() == p2.size()) && equivalentes(p1,p2,p1.size());
	
	if(res){
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
	}
}


	
