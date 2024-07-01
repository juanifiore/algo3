#include <iostream>
#include <queue>
#include <tuple>
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

int main(){
	int n = 5;
	vector<priority_queue<tuple<int,int>,vector<tuple<int,int>>,greater<tuple<int,int>>>> g(n);
	g[0].push(make_tuple(10,1));
	g[0].push(make_tuple(11,2));
	g[0].push(make_tuple(12,3));
	print(g[0]);	
	cout << get<0>(g[0].top()) << endl;
}	

