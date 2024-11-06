

#include<iostream>
#include<string>
#include<vector>
#include<utility>
using namespace std;


int main(){
       vector <pair<string,string>> dataMem;
       string d= "100000";
       dataMem.push_back(make_pair(d,"12345678"));
       cout<<dataMem[0].first<<"  " <<dataMem[0].second<<endl;
       string u = to_string(stoi(d) +1);
       dataMem.push_back(make_pair(u,"9101112"));
       cout<<dataMem[1].first<<"  " <<dataMem[1].second[2]<<endl;
       dataMem.push_back(make_pair("100002","131415"));
       dataMem.push_back(make_pair("100003","161718"));
       dataMem.push_back(make_pair("100004","192021"));
       dataMem.push_back(make_pair("100005","222324"));
        
       for(int i=0;i<6;i++){
        string m = to_string(stoi(d)+i);
         if(dataMem[i].first == m) cout<<dataMem[i].first<<"-"<<dataMem[i].second<<endl;	
         if(dataMem[i].first == m) cout<<dataMem[i].first<<"-"<<dataMem[i+1].second<<endl;	
         if(dataMem[i].first == m) cout<<dataMem[i].first<<"-"<<dataMem[i+1].second[4]<<endl;	
       }
	return 0;
}
