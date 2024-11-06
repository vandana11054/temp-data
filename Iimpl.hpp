

#include<iostream>
#include<string>
#include "binfunc.hpp"
using namespace std;

void igen(string func,string rd,string rs1,string imm,vector<pair<string,string>> * regs){
    int a=0;
    string temp;
    string adder;
    for(int i=4;i>=0;i--){
    int b=0;
      b+=(rs1[i]-'0');
      for(int k=1;k<5-i;k++){
	      b*=2;
      }
      a=a+b;
    }
   temp = regs->at(a).second;
   reverse(temp.begin(),temp.end());
   temp.pop_back();
   temp.pop_back();
   reverse(temp.begin(),temp.end());
   a=0;
    for(int i=4;i>=0;i--){
    int b=0;
      b+=(rd[i]-'0');
      for(int k=1;k<5-i;k++){
              b*=2;
      }
      a = a+b;
    }
	regs->at(a).second.erase();
	string src2;
        for(int k=0;k<temp.length();k++){
              src2.append(hex_to_bin(temp[k]));
	}
	string in;
	if(func == "addi")  in = binadd(imm,src2);
	if(func == "andi")  in = binand(imm,src2);
	if(func == "xori")  in = binxor(imm,src2);
	if(func == "ori")   in = binor(imm,src2);
	if(func == "slli")  in = binsll(src2,imm,func);
	if(func == "srli")  in = binsrl(src2,imm,func);
	if(func == "srai")  in = binsra(src2,imm,func);
	if(in.length()>64){
             reverse(in.begin(),in.end());
	     while(in.length()>64) in.pop_back();
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
	regs->at(a).second = adder;
}

void iload(string func,string rd,string rs1,string imm,vector<pair<string,string>> * regs,string* text,string* PC,vector<pair<string,string>> * data){
    int a=0;
    string temp;
    string adder;
    for(int i=4;i>=0;i--){
    int b=0;
      b+=(rs1[i]-'0');
      for(int k=1;k<5-i;k++){
	      b*=2;
      }
      a=a+b;
    }
   temp = regs->at(a).second;
   reverse(temp.begin(),temp.end());
   temp.pop_back();
   temp.pop_back();
   reverse(temp.begin(),temp.end());
     a=0;
    for(int i=4;i>=0;i--){
    int b=0;
      b+=(rd[i]-'0');
      for(int k=1;k<5-i;k++){
              b*=2;
      }
      a=a+b;
    }
	regs->at(a).second.erase();
	regs->at(a).second.append("0x");
	string src;
        for(int k=0;k<temp.length();k++){
              src.append(hex_to_bin(temp[k]));
	}
	if(imm.length()<src.length()){
              reverse(imm.begin(),imm.end());
	      while(imm.length()<src.length()){
                 imm.push_back(imm[imm.length()-1]);
	      }
              reverse(imm.begin(),imm.end());
	}
	cout<<"value  at rs1 is "<<src<<endl;
	cout<<"Imm at load is "<<imm<<endl;
	string in;
        in = binadd(src,imm);
	cout<<"In value at load is "<<in<<endl;
        int dec = 0;
      for(int i=in.length()-1;i>=0;i--){
      int b=0;
      if(in[i] == 1 && i==0) { b = -1;}
      else b = (in[i]-'0');
      for(int k=0 ;k<in.length()-1-i ; k++){
              b*=2;
      }
      dec = dec+b;
      }
      if(func == "ld"){
        for(int z=7;z>=0;z--){
		if(dec+z < 0){
	        regs->at(a).second.append("0");
                break;
		}
		string temp = text[dec+z]; //change here
		if(temp.empty()) { 
	            regs->at(a).second.append("0");
		    break;
		} 
		reverse(temp.begin(),temp.end());
		temp.pop_back();
		temp.pop_back();
		reverse(temp.begin(),temp.end());
	        regs->at(a).second.append(temp);
	}
      }
      if(func == "lw" || func == "lwu" ){
	      string word;
        for(int z=3;z>=0;z--){
		if(dec+z < 0){
	        regs->at(a).second.append("0");
                break;
		}
		string temp = text[dec+z];
		if(temp.empty()) { 
	            regs->at(a).second.append("0");
		    break;
		} 
		reverse(temp.begin(),temp.end());
		temp.pop_back();
		temp.pop_back();
		reverse(temp.begin(),temp.end());
	        word.append(temp);

      }
		reverse(word.begin(),word.end());
		if(word.length()<16){
		   if(func == "lw"){
		   if(0<=word[word.length()-1]-'0' && word[word.length()-1]-'0'<8){
                   while(word.length()<16)  word.push_back('0');
		   }else{
                   while(word.length()<16)  word.push_back('f');
		   }
		   }else if(func == "lwu"){
                   while(word.length()<16)  word.push_back('0');
		   }
		}
		reverse(word.begin(),word.end());
		regs->at(a).second = "0x";
	        regs->at(a).second.append(word);
		word.erase();
	}
      if(func == "lh"|| func == "lhu" ){
	      string half;
        for(int z=1;z>=0;z--){
		if(dec+z < 0){
	        regs->at(a).second.append("0");
                break;
		}
		string temp = text[dec+z];
		if(temp.empty()) { 
	            regs->at(a).second.append("0");
		    break;
		} 
		reverse(temp.begin(),temp.end());
		temp.pop_back();
		temp.pop_back();
		reverse(temp.begin(),temp.end());
	        half.append(temp);
      }
		reverse(half.begin(),half.end());
		if(half.length()<16){
			if(func=="lh"){
		   if(0<=half[half.length()-1]-'0' && half[half.length()-1]-'0'<8){
                   while(half.length()<16)  half.push_back('0');
		   }else{
                   while(half.length()<16)  half.push_back('f');
		   }
			}else if(func == "lhu"){
                        while(half.length()<16)  half.push_back('0');
			}
		}
		reverse(half.begin(),half.end());
		regs->at(a).second = "0x";
	        regs->at(a).second.append(half);
		half.erase();
	}
      if(func == "lb" || func == "lbu"){
	      string byt;
	      for(;;){
		if(dec < 0){
	        regs->at(a).second.append("0");
		break;
		}
		string temp = text[dec];
		if(temp.empty()) { 
	            regs->at(a).second.append("0");
		    break;
		} 
		reverse(temp.begin(),temp.end());
		temp.pop_back();
		temp.pop_back();
		reverse(temp.begin(),temp.end());
	        byt.append(temp);
		reverse(byt.begin(),byt.end());
		if(byt.length()<16){
		   if(func == "lb"){
		   if(0<= byt[byt.length()-1]-'0' && byt[byt.length()-1]-'0'<8){
                      while(byt.length()<16)  byt.push_back('0');
		   }else{
                      while(byt.length()<16)  byt.push_back('f');
		   }
		}else if(func == "lbu"){
                      while(byt.length()<16)  byt.push_back('0');
		}
		break;
	      }
		reverse(byt.begin(),byt.end());
		regs->at(a).second = "0x";
	        regs->at(a).second.append(byt);
		byt.erase();
	}
}
/*if(func == "jalr"){

}*/
}
