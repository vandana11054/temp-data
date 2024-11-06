


#include<iostream>
#include<string>
//#include "binfunc.hpp"
using namespace std;

void rgen(string func,string rd,string rs1,string rs2,vector<pair<string,string>> * regs){
    int a=0;
    string temp1;
    string temp2;
    string adder;
    for(int i=4;i>=0;i--){
    int b=0;
      b+=(rs1[i]-'0');
      for(int k=1;k<5-i;k++){
	      b*=2;
      }
      a=a+b;
    }
   temp1 = regs->at(a).second;
   reverse(temp1.begin(),temp1.end());
   temp1.pop_back();
   temp1.pop_back();
   reverse(temp1.begin(),temp1.end());
   a=0;
    for(int i=4;i>=0;i--){
    int b=0;
      b+=(rs2[i]-'0');
      for(int k=1;k<5-i;k++){
	      b*=2;
      }
      a=a+b;
    }
   temp2 = regs->at(a).second;
   reverse(temp2.begin(),temp2.end());
   temp2.pop_back();
   temp2.pop_back();
   reverse(temp2.begin(),temp2.end());
   a=0;
    for(int i=4;i>=0;i--){
    int b=0;
      b+=(rd[i]-'0');
      for(int k=1;k<5-i;k++){
              b*=2;
      }
      a=a+b;
    }
    
    if(temp1.length() < 16){
       reverse(temp1.begin(),temp1.end());
       while(temp1.length()<16){
       temp1.push_back(temp1[temp1.length()-1]);
    }
       reverse(temp1.begin(),temp1.end());
    }
    if(temp2.length() < 16){
       reverse(temp2.begin(),temp2.end());
       while(temp2.length()<16){
       temp2.push_back(temp2[temp2.length()-1]);
    }
       reverse(temp2.begin(),temp2.end());
    }

	regs->at(a).second.erase();
	string src1;
        for(int k=0;k<temp1.length();k++){
             src1.append(hex_to_bin(temp1[k]));
	}
	string src2;
        for(int p=0;p<temp2.length();p++){
              src2.append(hex_to_bin(temp2[p]));
	}
	bool comp = true;
	string sr;
	if(func == "sub"){
		reverse(src2.begin(),src2.end());
		int u=0;
               for(;u<64;u++){ 
	//loop for calculating 2's complement of a given  binary number
                   if(src2[u]==1+'0'){ //encounter left-most one (still src2. is not reversed)
                            comp =false;
			    for(int i=0;i<=u;i++){
                               sr.push_back(src2[i]);
			    }
			    for(int k=u+1;k<64;k++){ //flip all other bits that are left
               if(src2[k]==0+'0') sr.push_back(1+'0'); 
	       else if(src2[k]==1+'0') sr.push_back(0+'0');
			    }
		   }
	     if(comp ==false) break;
	       if(comp == true && u == 63) {
                            for(int p=0;p<64;p++) {  sr.push_back(0+'0');}
	       }
	       }
		reverse(src2.begin(),src2.end());
		reverse(sr.begin(),sr.end());
	}
	string in;
	if(func == "add")  in = binadd(src1,src2);
	if(func == "sub")  in = binadd(src1,sr);
	if(func == "and")  in = binand(src1,src2);
	if(func == "xor")  in = binxor(src1,src2);
	if(func == "or")   in = binor(src1,src2);
	if(func == "sll")  in = binsll(src1,src2,func);
	if(func == "srl")  in = binsrl(src1,src2,func);
	if(func == "sra")  in = binsra(src1,src2,func);
	if(in.length() > 64){
		reverse(in.begin(),in.end());
           in.pop_back();
		reverse(in.begin(),in.end());
	}
  	for(int i=0;i<in.length();i=i+4){
		string bin = in.substr(i,4);
		char c= conv(stoi(bin));
		adder.push_back(c);
	}
	if(adder.length()<18){
           reverse (adder.begin(),adder.end());
	   while(adder.length()<16){
                if(0<=adder[adder.length()-1]-'0' && adder[adder.length()-1]-'0'<8)
		       	adder.push_back('0');
		else adder.push_back('f');
	   }
	   adder.push_back('x');
	   adder.push_back('0');
           reverse (adder.begin(),adder.end());
	}
	regs->at(a).second.erase();
	regs->at(a).second.append(adder);
}
