#include<iostream>
#include<fstream>
#include<bits/stdc++.h>

using namespace std;
using namespace std::chrono;
string input = "data_int.txt";
string query_file = "queries_new.txt" ;
// const int size = 1e6;
// const int feature_size = 100;
// const int queries_size = 100 ; 
#define size 1e7
#define feature_size 100
#define queries_size 100
volatile int current_query = 0 ;

vector<int> row(feature_size);
vector<vector<int>> data(size);
vector<vector<int>> queries(queries_size);
vector<int> squares(201);
vector<pair<int,int>> answer[queries_size];
vector<float> query_time(queries_size);

int read_data(){
	ifstream file(input);
	if(file.is_open()){
		string number;
		for(int i=0;i<size;i++){
			int j = 0;
			for (j;j<feature_size-1;j++){
				getline(file,number,' ');
				//cout<<stof(number)<<" "<<flush;
				data[i][j] = stoi(number);
			}
			getline(file,number,'\n');
			data[i][j] = stoi(number);
		}
		file.close();
		return 0;
	}
	else{
		cout<<"Error reading data\n";
		return 1;
	}
}
int read_queries(){
	ifstream quer(query_file);
	if(quer.is_open()){
		string number;
		for(int i=0;i<queries_size;i++){
			int j = 0;
			for (j;j<feature_size-1;j++){
				getline(quer,number,' ');
				queries[i][j] = stoi(number);
			}
			getline(quer,number,'\n');
			queries[i][j] = stoi(number);
		}
		quer.close();
		return 0;
	}
	else{
		cout<<"Error reading queries\n";
		return 1;
	}
}
inline int euclDist(vector<int>& current_row, int top_d) {
	int distance = 0 ;
	for(int i=0;i<feature_size;i++) {
		int diff = abs(current_row[i]-queries[current_query][i]);
		distance += squares[diff];
		if(distance>=top_d)
			return INT_MAX;
	}
	return distance;
}
inline void solve( int query_num) {
	priority_queue<pair<int,int>> closer_vectors;
	int index = 0;
	while(index<10) {
		int d = euclDist(data[index],INT_MAX);
		pair<float,int> elem;
		elem = make_pair(d,index);
		closer_vectors.push(elem);
		index++;
	}
	while(index<size) {
		pair<int,int> elem = closer_vectors.top();
		int d = euclDist(data[index],elem.first);
		if(elem.first>d) {
			closer_vectors.pop();
			closer_vectors.push(make_pair(d,index));	       
		}
		index++;		
	}
	// cout<<"Closest vectors to given query vector are : \n" ;

	while(!closer_vectors.empty()){
		int dist = closer_vectors.top(). first;
		int ind = closer_vectors.top().second ;
		// cout<<ind<<" : "<<dist<<"\n";
		answer[query_num].push_back({ind,dist});
		closer_vectors.pop() ; 
	}
}
inline void populate_tables() {
    for(int i=0;i<size;i++){
		data[i] = row;
		i<queries_size? queries[i] = row :row ;
	}	
    for(int i=0;i<=200;i++) 
        squares[i] = i*i;
}
inline void print_values(){
	for(int i =0;i<queries_size;i++){
		cout<<"QUERY "<<i<<" : \n";
		for(int j =0;j<10;j++){
			cout<<answer[i][j].first<<" : "<<answer[i][j].second<<"\n";
		}
		cout<<"Time : "<<query_time[i]<<" seconds!!"<<"\n";
	}

}
inline void find_median(){
    size_t n = feature_size/2;
    nth_element(query_time.begin(),query_time.begin()+n,query_time.end());
    float median = query_time[n];
    cout<<"Median time taken : "<<median<<" seconds!!\n";
}
int main()
{
    populate_tables();
	read_data();
	read_queries();
	while(current_query<queries_size) {
		// cout<<"For query "<<i+1<<" : \n";
		auto start = high_resolution_clock::now();
		solve(current_query);
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		query_time[current_query] = (float(duration.count())/1000000); 
        current_query++;

	}
	print_values();
    find_median();
}
