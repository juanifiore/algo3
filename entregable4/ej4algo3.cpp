#include <iostream>
#include <string>
#include <vector>

using namespace std;


bool equivalentStrings (string& string1, string& string2, int largo){
    if (largo % 2 == 1){
        return string1 == string2; 
    } else {
        string m11 = string1.substr(0, largo/2);
        string m12 = string1.substr(largo/2, largo/2);
        string m21 = string2.substr(0, largo/2);
        string m22 = string2.substr(largo/2, largo/2);


        if(equivalentStrings(m11, m21, largo/2)){
            return equivalentStrings(m12, m22, largo/2);
        }
        else{
            return equivalentStrings(m12, m21, largo/2) && equivalentStrings(m11, m22, largo/2);
        }
        
       

    }
}



int main(){ 
string string1;
cin>>string1;
string string2;
cin>>string2;

int largo1 = string1.size();
int largo2 = string2.size();
if(largo1 == largo2 && equivalentStrings(string1, string2, largo1)){
    cout<<"YES"<<endl;
}
else{
    cout<<"NO"<<endl;
}

return 0;
}
