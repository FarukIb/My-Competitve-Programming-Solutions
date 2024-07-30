#include <iostream>
#include <vector>

using namespace std;

void setup(vector <int>&v1,vector <int>&v2,vector <int>&v3,int br){
    v1.clear();
    v2.clear();
    v3.clear();
    for(int i=br;i>0;i--){
        v1.push_back(i);
    }
}

void print(const vector <int>&v1,const vector <int>&v2,const vector <int>&v3, int br=0){
    cout << "Korak "<<br<<endl;
    cout <<" :";
    for(int i=0;i<v1.size();i++){
        cout <<v1[i]<< " ";
    }
    cout << endl;
    cout <<" :";
    for(int i=0;i<v2.size();i++){
        cout <<v2[i]<< " ";
    }
    cout << endl;
    cout <<" :";
    for(int i=0;i<v3.size();i++){
        cout <<v3[i]<< " ";
    }
    cout << endl;
}

void recur(int br, int from, int to, int pom, vector<pair<int,int> >& arr)
{
    if(br==0) return;

    recur(br-1,from,pom,to, arr);
    
    arr.push_back(pair<int,int>(from,to));
    recur(br-1,pom,to,from,arr);
    
}

void editPrint(vector <int>&v1,vector <int>&v2,vector <int>&v3, pair<int,int>p)
{
	int temp;
	if(p.first==0){
		temp=v1[v1.size()-1];
		v1.pop_back();
	}
	else if(p.first==1){
		temp=v2[v2.size()-1];
		v2.pop_back();
	}
	else if(p.first==2){
		temp=v3[v3.size()-1];
		v3.pop_back();
	}
	if(p.second==0){
		v1.push_back(temp);
	}
	else if(p.second==1){
		v2.push_back(temp);
	}
	else if(p.second==2){
		v3.push_back(temp);
	}
}

int main()
{
    vector <int> pos1,pos2,pos3;
    vector <pair<int,int> >arr;
    int br_ploca=3;
    cout << "Unesi broj plocica: ";
    cin>>br_ploca;
    setup(pos1,pos2,pos3,br_ploca);
    print(pos1,pos2,pos3);

    recur(br_ploca,0,2,1,arr);

	//ispis
	for(int i=0;i<arr.size();i++) {
		editPrint(pos1,pos2,pos3,arr[i]);
		cout << endl;
		print(pos1,pos2,pos3,i+1);
	}
    return 0;
}
