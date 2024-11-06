

#include<iostream>
#include<string>
using namespace std;

string Opcode(string a){
	if(a=="add" || a=="sub"||a=="xor"||a=="or"||a=="and"||a=="sll"||a=="srl"||a=="sra")   return "0110011" ;                                                  
	else if(a=="addi"|| a=="xori"||a=="ori"||a=="andi"||a=="slli"||a=="srli"||a=="srai") return "0010011";
	else if(a=="lb"||a=="lh"||a=="ld"||a=="lw"||a=="lhu"||a=="lbu"||a=="lwu") return "0000011";
	else if(a=="sw"||a=="sd"||a=="sh"||a=="sb") return "0100011";
	else if(a=="blt"||a=="beq"||a=="bne"||a=="bge"||a=="bgeu"||a=="bltu") return "1100011";
	else if(a=="lui") return "0110111";
	else if(a=="jalr") return "1100111"; 
	else if(a=="jal") return "1101111"; 
        return "invalid";	
}
char conv(int a){
	switch(a){
		case 0:  return '0';
			 break;
		case 1: return '1' ;
			break;
		case 10: return '2' ;
			 break;
		case 11:  return '3';
			  break;
		case 100: return '4' ;
			  break;
		case 101:  return '5';
			   break;
		case 110: return '6';
			  break;
		case 111:  return '7';
			   break;
		case 1000:  return '8';
			    break;
		case 1001:  return '9';
			    break;
		case 1010:  return 'a';
			    break;
		case 1011: return 'b' ;
			   break;
		case 1100:  return 'c';
			    break;
		case 1101: return 'd' ;
			   break;
		case 1110:  return 'e';
			    break;
		case 1111:  return 'f';
			    break;
	}
	return '0';
}

string dec_to_bin(int a){
	switch(a){
		case 0:  return "0000";
			 break;
		case 1: return "0001";
			break;
		case 2: return "0010" ;
			break;
		case 3:  return "0011";
			 break;
		case 4: return  "0100";
			break;
		case 5:  return "0101";
			 break;
		case 6: return "0110";
			break;
		case 7:  return "0111";
			 break;
		case 8:  return "1000";
			 break;
		case 9:  return "1001";
			 break;
		case 10:  return "1010";
			  break;
		case 11: return  "1011";
			 break;
		case 12:  return "1100";
			  break;
		case 13: return  "1101";
			 break;
		case 14:  return "1110";
			  break;
		case 15:  return "1111";
			  break;
	}
	return "error";
}

string hex_to_bin(char a){
  switch(a){
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'a': return "1010";
        case 'b': return "1011";
        case 'c': return "1100";
        case 'd': return "1101";
        case 'e': return "1110";
        case 'f': return "1111";
  }
  return "error";
}

string reg(string a){
	if(a=="x0" || a=="zero")   return "00000" ;                                                  
	else if(a=="x1"|| a=="ra") return "00001";                                                                                    
	else if(a=="x2"|| a=="sp") return "00010";                                                                                   
	else if(a=="x3"|| a=="gp") return "00011";                                                                                   
	else if(a=="x4"|| a=="tp") return "00100";                                                                                   
	else if(a=="x5"|| a=="t0") return "00101";                                                                                   
	else if(a=="x6"|| a=="t1") return "00110";                                                                                    
	else if(a=="x7"|| a=="t2") return "00111";                                                                                   
	else if(a=="x8"|| a=="s0"||a=="fp") return "01000";                                                                                    
	else if(a=="x9"|| a=="s1") return "01001";                                                                                    
	else if(a=="x10"|| a=="a0") return "01010";                                                                                    
	else if(a=="x11"|| a=="a1") return "01011";                                                                                    
	else if(a=="x12"|| a=="a2") return "01100";
	else if(a=="x13"|| a=="a3") return "01101"; 
	else if(a=="x14"|| a=="a4") return "01110";                                                                                    
	else if(a=="x15"|| a=="a5") return "01111";
	else if(a=="x16"|| a=="a6") return "10000";
	else if(a=="x17"|| a=="a7") return "10001";
	else if(a=="x18"|| a=="s2") return "10010";
	else if(a=="x19"|| a=="s3") return "10011";
	else if(a=="x20"|| a=="s4") return "10100";
	else if(a=="x21"|| a=="s5") return "10101";
	else if(a=="x22"|| a=="s6") return "10110";
	else if(a=="x23"|| a=="s7") return "10111";
	else if(a=="x24"|| a=="s8") return "11000";
	else if(a=="x25"|| a=="s9") return "11001";
	else if(a=="x26"|| a=="s10") return "11010";
	else if(a=="x27"|| a=="s11") return "11011";
	else if(a=="x28"|| a=="t3") return "11100";
	else if(a=="x29"|| a=="t4") return "11101";
	else if(a=="x30"|| a=="t5") return "11110";
	else if(a=="x31"|| a=="t6") return "11111";
	else return "invalid";
}

string PCU(string PC,string b){
      string res;
      reverse(PC.begin(),PC.end());
      PC.pop_back();
      PC.pop_back();
      reverse(PC.begin(),PC.end());
      int q=0;
      string a;
      for(int d=0;d<PC.length();d=d+1){
        a.append(hex_to_bin(PC[d]));
      }
int k=a.length()-b.length()-1;
reverse(b.begin(),b.end());
for(;k>=0;k--){
     b.push_back('0');
}
reverse(b.begin(),b.end());
for(int i= a.length()-1;i>=0;i--){
      int p = (a[i]-'0')+(b[i]-'0')+q;
      if(p == 2) {
	      res.push_back('0'); 
              q=1;
      }
      else if(p<2){
	      res.push_back(p + '0'); 
	      q=0;
      }else if(p==3){
              res.push_back(1+'0');
	      q=1;
      }
      }
if(q){
        res.push_back(q+'0');
}
      reverse(res.begin(),res.end());
      if(res.length()>64){
          reverse(res.begin(),res.end());
	  while(res.length()>64) res.pop_back();
          reverse(res.begin(),res.end());
      }
      PC.erase();
	for(int i=0;i<res.length();i=i+4){
		string bin = res.substr(i,4);
		char c= conv(stoi(bin));
		PC.push_back(c);
	}
      res.erase();
      reverse(PC.begin(),PC.end());
      PC.push_back('x');
      PC.push_back('0');
      reverse(PC.begin(),PC.end());
      return PC;
}

void reg_val(string a,string val,vector<pair<string,string>> *regs){
	if(a== "00000")  {
	      regs->at(0).first = a;
	      regs->at(0).second = val;
	}		
	else if(a=="00001") {
	      regs->at(1).first = a;
	      regs->at(1).second = val;
	}		
	else if(a=="00010") 
	{
	      regs->at(2).first = a;
	      regs->at(2).second = val;
	}		
	else if(a=="00011")                                                                         {
	      regs->at(3).first = a;
	      regs->at(3).second = val;
	}		
	else if(a=="00100")                                                               	{
	      regs->at(4).first = a;
	      regs->at(4).second = val;
	}		
	else if(a=="00101")                                                                         {
	      regs->at(5).first = a;
	      regs->at(5).second = val;
	}		
	else if(a=="00110")                                                                    	{
	      regs->at(6).first = a;
	      regs->at(6).second = val;
	}		
	else if(a=="00111")                                                                                    
	{
	      regs->at(7).first = a;
	      regs->at(7).second = val;
	}		
	else if(a=="01000")                                                                                     
	{
	      regs->at(8).first = a;
	      regs->at(8).second = val;
	}		
	else if(a=="01001")                                                                                     
	{
	      regs->at(9).first = a;
	      regs->at(9).second = val;
	}		
	else if(a=="01010")                                                                                     
	{
	      regs->at(10).first = a;
	      regs->at(10).second = val;
	}		
	else if(a=="01011")                                                                                     
	{
	      regs->at(11).first = a;
	      regs->at(11).second = val;
	}		
	else if(a=="01100") 
	{
	      regs->at(12).first = a;
	      regs->at(12).second = val;
	}		
	else if(a=="01101") 
	{
	      regs->at(13).first = a;
	      regs->at(13).second = val;
	}		
	else if(a=="01110") 
	{
	      regs->at(14).first = a;
	      regs->at(14).second = val;
	}		
	else if(a=="01111") 
	{
	      regs->at(15).first = a;
	      regs->at(15).second = val;
	}		
	else if(a=="10000") 
	{
	      regs->at(16).first = a;
	      regs->at(16).second = val;
	}		
	else if(a=="10001") 
	{
	      regs->at(17).first = a;
	      regs->at(17).second = val;
	}		
	else if(a=="10010")
	{
	      regs->at(18).first = a;
	      regs->at(18).second = val;
	}		
	else if	(a=="10011")
	{
	      regs->at(19).first = a;
	      regs->at(19).second = val;
	}		
	else if(a=="10100") 
	{
	      regs->at(20).first = a;
	      regs->at(20).second = val;
	}		
	else if(a=="10101") 
	{
	      regs->at(21).first = a;
	      regs->at(21).second = val;
	}		
	else if(a=="10110") 
	{
	      regs->at(22).first = a;
	      regs->at(22).second = val;
	}		
	else if(a=="10111") 
	{
	      regs->at(23).first = a;
	      regs->at(23).second = val;
	}		
	else if(a=="11000") 
	{
	      regs->at(24).first = a;
	      regs->at(24).second = val;
	}		
	else if(a=="11001") 
	{
	      regs->at(25).first = a;
	      regs->at(25).second = val;
	}		
	else if(a=="11010") 
	{
	      regs->at(26).first = a;
	      regs->at(26).second = val;
	}		
	else if(a=="11011") 
	{
	      regs->at(27).first = a;
	      regs->at(27).second = val;
	}		
	else if(a=="11100") 
	{
	      regs->at(28).first = a;
	      regs->at(28).second = val;
	}		
	else if(a=="11101") 
	{
	      regs->at(29).first = a;
	      regs->at(29).second = val;
	}		
	else if(a=="11110") 
	{
	      regs->at(30).first = a;
	      regs->at(30).second = val;
	}		
	else if(a=="11111") 
	{
	      regs->at(31).first = a;
	      regs->at(31).second = val;
	}		
}
