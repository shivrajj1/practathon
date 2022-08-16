#include<iostream>
#include<random>
#include<fstream>
#include<string>	

using namespace std;

const int size = 1e7;
// const float mean = 0.0;
// const float stddev = 100.0;
const int high = 100;
const int low = -100;
const int feature_size = 100;
//int total_nums_to_generate = size*feature_size;
unsigned seed = time(0);
default_random_engine generator(seed);
uniform_int_distribution<int> distribution(low,high);
void generate_(ofstream& file){
	for(int i=0;i<size;i++){
		for(int j=0;j<feature_size-1;j++){
			string num = to_string(distribution(generator)) ; 
			file << num <<" ";
		}
		string num = to_string(distribution(generator)) ; 
		file << num <<"\n";

	}

}
int main()
{		
	// Seed the random number generator.
	srand(seed);	
	ofstream file("data_int.txt");
	if(file.is_open()){
		generate_(file);
		file.close();
	}
	else {
		cout<<"Error while opening file\n";
		return 1;
	}


}
