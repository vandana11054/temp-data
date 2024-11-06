

#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<utility>
#include"functions.hpp"
#include"Iimpl.hpp"
#include"Rimpl.hpp"
#include"Simpl.hpp"
#include"Uimpl.hpp"
#include"Bimpl.hpp"
#include"Jimpl.hpp"
using namespace std;

string Rfunc7(string a){
	if(a=="sra" || a=="sub")   return "0100000" ;                                                  
	else if(a=="add"||a=="xor"||a=="or"||a=="and"||a=="sll"||a=="srl") 
		return "0000000";                                                   
	return "error";                                                 
}
string Rfunc3(string a){
	if(a=="add" || a=="sub")   return "000" ;                                                  
	else if(a=="srl"|| a=="sra") return "101";                                                   
	else if(a=="sll") return "001";                                                   
	else if(a=="xor") return "100";                                                                                   
	else if(a=="or") return "110";                                                
	else if(a=="and") return "111";                                               
	return "error";

}

string Sfunc3(string a)
{
	if(a=="sb")
		return "000";
	else if(a=="sh")
		return "001";
	else if(a=="sw")
		return "010";
	else if(a=="sd")
		return "011";
	return "error";
}
string Ifunc3(string a)
{
	if (a == "addi")
		return "000";

	else if (a == "xori")
		return "100";

	else if (a == "ori")
		return "110";

	else if (a == "andi")
		return "111";

	else if (a == "slli")
		return "001";

	else if (a == "srli")
		return "101";

	else if (a == "srai")
		return "101";

	else if (a == "jalr")
		return "000";
	else if (a == "lb")
		return "000";
	else if (a == "lh")
		return "001";
	else if (a == "lw")
		return "010";
	else if (a == "ld")
		return "011";
	else if (a == "lbu")
		return "100";
	else if (a == "lhu")
		return "101";
	else if (a == "lwu")
		return "110";
	return "error";
}
string Ifunc6(string a)
{
	if (a == "slli")
		return "000000";

	else if (a == "srli")
		return "000000";

	else if (a == "srai")
		return "010000";
	return "error";
}
string Bfunc3(string func){        //3 bits of func3 returned
	if(func=="beq") return "000";
	else if(func=="bne") return "001";
	else if(func=="blt") return "100";
	else if(func=="bge") return "101";
	else if(func=="bltu") return "110";
	else if(func=="bgeu") return "111";
	return "error3";    //invalid function 
}
string constant(string imm,string value,string Opcode){
	//function to provide a 20 bit binary value for a decimal number(string value)
	int temp = stoi(value); // convert value to integer 
	if((temp>= -2048 && temp<=2047)||(temp>=-4096 && temp<=4094 && Opcode=="1100011" )){
		//for B format range of immediate is [-4096,4094] 
		//for I,S  formats range of immediate is [-2048,2047]
		if(temp<0){ // if immediate is negative
			bool a= true; 
			// variable that indicates right-most one is met or not for calculating 2's
			// complement in simple method
			temp = 0-temp; //convert imm to positive
			int i=0;
			for(;i<12;i++){ //loop for generating binary equivalent of  +ve decimal number
				imm.push_back(temp%2 + '0'); 
				temp = temp/2;
				if(temp==1){
					imm.push_back(1+'0');
					i++;
					break;
				}
			}
			while(i<11){ //if number of bits in immediate's binary form < 12 
				imm.push_back('0');
				i++;
			}
			for(int u=0;u<11;u++){ 
				//loop for calculating 2's complement of a given  binary number
				if(imm[u]==1+'0'){ //encounter left-most one (still imm. is not reversed)
					a=false;
					for(int k=u+1;k<12;k++){ //flip all other bits that are left
						if(imm[k]==0+'0') imm[k]=1+'0'; 
						else if(imm[k]==1+'0') imm[k]=0+'0';
					}
				}
				if(a==false) break;
			}
		}
		else{  //if immediate value is positive 
			int i=0;
			for(;i<12;i++){ //loop for generating binary equivalent of  +ve decimal number
				imm.push_back(temp%2 + '0');
				temp = temp/2;
				if(temp==1){
					imm.push_back(1+'0');
					i++;
					break;
				}
			}
			while(i<11){ //if number of bits in immediate's binary form < 12
				imm.push_back(0+'0');
				i++;
			}
		}
		reverse(imm.begin(),imm.end());//now reverse string imm to get correct binary value
		return imm;
	}else{
		return "rangeError"; //out_of_range error 
	}
}
string Bformat(string line,string rs1,string rs2,string func,string imm,string in,int i,int count,vector<pair<int,string>> label,vector<pair<string,string>> * regs,string * PC,string *exec,int * stepper){
	//function to generate binary format of given instruction
	bool next = true;
	i++;
	for(;i<line.length();i++){
		if(line[i]!=',' && !(isspace(line[i]))){
			//second argument(rs1) terminates at comma or space
			next = false;
			rs1.push_back(line[i]);
		}
		else if(line[i]==',') break;
	}
	i++;
	next = true;
	for(;i<line.length();i++){
		if(line[i]!=','&& !(isspace(line[i]))){
			// rs2 terminates with comma or space
			next = false;
			rs2.push_back(line[i]);
		}
		else if(line[i]==',' && !(next)) break;
	}
	next =true;
	string target;  // string to  store decimal immediate value
	for(;i<line.length();i++){
		if(line[i]!=','&& !(isspace(line[i]))){
			next = false;
			target.push_back(line[i]);
		}
	}
	for(int m=0;m<label.size();m++){
		if(label[m].second == target){ 
			*stepper = label[m].first;
			imm =constant(imm,to_string(4*(label[m].first-count)),Opcode(func));
			//label[m].first returns line number of given label
			// label[m].first-count returns no. of lines between label and b-instruction with label 
			break;
		}
		if(label[m].second != target && m==label.size()-1){
			//label not found in vector of pairs (label) 	
			cout<<"label at line "<<count<<" not found"<<endl;
			return "1";
		}
	}
	if(imm.empty()){
		//empty label
		cout<<"Empty label found at line "<<count<<endl;
		return "1";
	}
	bgen(func,reg(rs1),reg(rs2),imm,regs,PC,exec,&count,stepper);
	if(!imm.empty() && (imm != "rangeError")){

		// ignore last bit(imm[0]) and sign-extend 
		imm.pop_back();
		reverse(imm.begin(),imm.end());
		if(imm[10] == 0+'0') imm.push_back(0+'0');
		else if(imm[10] == 1+'0') imm.push_back(1+'0');
		reverse(imm.begin(),imm.end());	  
	}
	if(imm != "rangeError") {  
		in.append(imm.substr(0,1));//imm[12]
		in.append(imm.substr(2,6));//imm[10:5]
	}else{
		cout<<"Immediate out of range in line "<<count<<endl;
		return "1";
	}
	if(reg(rs2)!="invalid")  {
		in.append(reg(rs2));
	}else{
		cout<<"Invalid identifier at source register-2 in line "<<count<<endl;
		return "1"; 
	}
	if(reg(rs1)!="invalid"){
		in.append(reg(rs1));
	}else{
		cout<<"Invalid identifier at source register-1 in line "<<count<<endl;
		return "1"; 
	}
	if(Bfunc3(func)!="error3") { //3 bits of func3 appended
		in.append(Bfunc3(func));
	}else{
		cout<<"Suspected wrong function syntax in line "<<count<<endl;
		return "1";
	}
	if(imm != "rangeError"){
		in.append(imm.substr(8,4)); //imm[4:1]
		in.append(imm.substr(1,1)); //imm[11]
	}
	in.append(Opcode(func));
	return in;
}

string Rformat(string line,string rd,string rs1,string rs2,string func,string in,int i,
		vector<pair<string,string>> * regs){
	bool next = true;
	i++;
	for(;i<line.length();i++){
		if(line[i]!=',' && !(isspace(line[i]))){
			next = false;
			rd.push_back(line[i]);
		}
		else if(line[i]==',') break;
	}
	i++;
	next = true;
	for(;i<line.length();i++){
		if(line[i]!=','&& !(isspace(line[i]))){
			next = false;
			rs1.push_back(line[i]);
		}
		else if(line[i]==',' && !(next)) break;
	}
	if(Rfunc7(func)=="error"){
		cout<<"Invalid operation in the instruction"<<endl;
		return "1";
	}else{
		in.append(Rfunc7(func));
	}
	i++;
	next =true;
	for(;i<line.length();i++){
		if(line[i]!=','&& !(isspace(line[i]))){
			next = false;
			rs2.push_back(line[i]);
		}
		else if(line[i]==',' && !(next)) break;
	}
	if(reg(rs2)!="invalid")  in.append(reg(rs2));
	if(reg(rs1)!="invalid")  in.append(reg(rs1));
	if(Rfunc3(func)!="error") in.append(Rfunc3(func));
	if(reg(rd)!="invalid")  in.append(reg(rd));
	rgen(func,reg(rd),reg(rs1),reg(rs2),regs);	
	in.append(Opcode(func));
	return in;
}
string lowerConstant(string imm,string value){
	int temp = stoi(value);
	int i=0;
	for(;i<6;i++){
		imm.push_back(temp%2 + '0');
		temp = temp/2;
		if(temp==1){
			imm.push_back(1+'0');
			i++;
			break;
		}
	}
	while(i<5){
		imm.push_back('0');
		i++;
	}
	reverse(imm.begin(),imm.end());
	return imm;
}
string Sformat(string line,string rs1,string rs2,string func,string imm,string in,int i,int count,vector<pair<string,string>> * regs,string* text,vector<pair<string,string>> * data){
	i++;
	for(;i<line.length();i++){
		if(!isspace(line[i]) && line[i]!=','){
			//second argument terminating characters are comma and blank space
			rs2.push_back(line[i]);
		}
		else if(line[i]==',' ) break;
	}
	string temp;
	i++;
	for(;i<line.length();i++){
		if(((int)line[i] <=57 && (int)line[i] >= 48 && !(isspace(line[i])))||(int)line[i]==45){  // number or minus sign is pushed to temporary string
			temp.push_back(line[i]);
		}
		else if(line[i]=='(') break;  // stop storing at (
	}
	imm =  constant(imm,temp,Opcode(func)); //binary immediate initialised
	bool next = true;
	i++;
	for(;i<line.length(); i++){
		if(line[i]!=')' && line[i]!='(' && !(isspace(line[i]))){
			// argument of form (arg.) stored in rs1
			next = false;
			rs1.push_back(line[i]);
		}
		else if(line[i]==')' && !(next)) break; //stop storing at )
	}
	if(imm != "rangeError") {
		in.append(imm.substr(0,7)); //imm[11:5]
	}else{
		cout<<"Immediate out of range in line "<<count<<endl;
		return "1";
	}
	if(reg(rs2)!="invalid") {
		in.append(reg(rs2));  //append 5 bits of source register
	}else{
		cout<<"Invalid identifier at source register-2 in line "<<count<<endl;
		return "1"; 
	}
	if(reg(rs1)!="invalid"){
		in.append(reg(rs1)); //append 5 bits of source register
	}else{
		cout<<"Invalid identifier at source register-1 in line "<<count<<endl;
		return "1"; 
	}
	if(Sfunc3(func)!="error3") { //3 bits of func3 appended
		in.append(Sfunc3(func));
	}else{
		cout<<"Suspected syntax error at function in line "<<count<<endl;
		return "1";
	}
	if(imm != "rangeError")  in.append(imm.substr(7,5));//imm[4:0]
	in.append(Opcode(func));
	store(func,reg(rs2),reg(rs1),imm,regs,text,data);	
	return in;
}
string IGformat (string line,string rs1,string func,string imm,string rd,string in,int i,int count,vector<pair<string,string>> * regs){ //function for general I-format instruction parsing
	bool next = true;
	i++;
	for(;i<line.length();i++){
		if(line[i]!=',' && !(isspace(line[i]))){
			//second argument(rd) terminates with comma or space
			next = false;
			rd.push_back(line[i]);
		}
		else if(line[i]==',') break;
	}
	i++;
	next = true;
	for(;i<line.length();i++){
		if(line[i]!=','&& !(isspace(line[i]))){
			//third argument(rs1) terminates with comma or space
			next = false;
			rs1.push_back(line[i]);
		}
		else if(line[i]==',' && !(next)) break;
	}
	i++;
	string temp;
	for(;i<line.length();i++){
		if(((int)line[i] <=57 && (int)line[i] >= 48)||(int)line[i]==45){
			//digits or minus symbol appended to string
			temp.push_back(line[i]);
		}
	}
	if(func=="slli" || func=="srli" || func=="srai"){
		imm =  lowerConstant(imm,temp); //6 bit immediate value
		if(Ifunc6(func)!="error6") {
			in.append(Ifunc6(func)); // 6 bits of func6 appended
		}else{
			cout<<"Suspected syntax error at function in line "<<count<<endl;
			return "1";
		}
		if(imm == "rangeError"){
			cout<<"Immediate out of range in line "<<count<<endl;
			return "1"; 
		}	
		in.append(imm); 
	}else{
		imm =  constant(imm,temp,Opcode(func)); //12 bit binary number
		if(imm == "rangeError"){
			cout<<"Immediate value provided is out of range in line "<<count<<endl;
			return "1";
		}
		in.append(imm);
	}
	if(reg(rs1)!="invalid"){
		in.append(reg(rs1));
	}else{
		cout<<"Invalid identifier at source register in line "<<count<<endl;
		return "1"; 
	}
	if(Ifunc3(func)!="error") {
		in.append(Ifunc3(func)); 
	}else{
		cout<<"Suspected syntax error at function in line "<<count<<endl;
		return "1";
	}
	if(reg(rd)!="invalid") {
		in.append(reg(rd));
	}else{
		cout<<"Invalid identifier at destination register in line "<<count<<endl;
		return "1"; 
	}
	igen(func,reg(rd),reg(rs1),imm,regs);	
	in.append(Opcode(func));
	return in;
}
string  ILformat( string line,string rs1,string func,string imm,string rd,string in,int i,int count,string* text,vector<pair<string,string>> * regs,string * PC,string* exec,int* stepper,vector<pair<string,string>> * data){ 
	//function for  I-format load instruction parsing      
	i++;
	for(;i<line.length();i++){
		if(!isspace(line[i]) && line[i]!=','){
			//second argument(rd) terminating characters are comma and blank space
			rd.push_back(line[i]);
		}
		else if(line[i]==',' ) break;
	}

	string temp;
	i++;
	for(;i<line.length();i++){
		if(((int)line[i] <=57 && (int)line[i] >= 48)||(int)line[i]==45){
			// digit or minus sign is appended
			temp.push_back(line[i]);
		}
		else if(line[i]=='(') break;
	}
	imm =  constant(imm,temp,Opcode(func));
	if(imm == "rangeError") {
		cout<<"Immediate value provided is out of range in line "<<count<<endl;
		return "1";
	}
	in.append(imm);
	bool next = true;
	i++;
	for(;i<line.length(); i++){
		if(line[i]!=')' && line[i]!='(' && !(isspace(line[i]))){
			//input is of the form (rs1)
			next = false;
			rs1.push_back(line[i]);
		}
		else if(line[i]==')' && !(next)) break;
	}
	if(reg(rs1)!="invalid"){
		in.append(reg(rs1));
		iload(func,reg(rd),reg(rs1),imm,regs,text,PC,data);	
	}else{
		cout<<"Invalid identifier at source register-1 in line "<<count<<endl;
		return "1"; 
	}
	if(Ifunc3(func)!="error") { //3 bits of func3 appended
		in.append(Ifunc3(func));
	}else{
		cout<<"Suspected wrong function syntax in line "<<count<<endl;
		return "1";
	}
	if(reg(rd)!="invalid") {
		in.append(reg(rd));
	}else{
		cout<<"Invalid identifier at destination register in line "<<count<<endl;
		return "1"; 
	}
	in.append(Opcode(func));
	return in; //binary instruction returned
}
string upperConstant(string imm,string value,string Opcode){
	//function for calculating 20-bit binary equivalent of a decimal number 
	int temp = stoi(value);
	if((Opcode == "0110111" && temp>=-524288 && temp<=524287)||(Opcode == "1101111" && temp>=-1048576 && temp<=1048574)){ 
		if(temp<0){   //if immediate is negative
			bool a = true;
			temp = 0-temp;
			int i=0;
			for(;i<20;i++){  //calculates binary form of decimal (in reverse order)
				imm.push_back(temp%2 + '0');
				temp = temp/2;
				if(temp==1){
					imm.push_back(1+'0');
					i++;
					break;
				}
			}
			while(i<19){  //if imm. less than 20 bits
				imm.push_back(0+'0');
				i++;
			}
			for(int u=0;u<19;u++){ //loop for calculating 2's complement
				if(imm[u]==1+'0'){
					a=false;
					for(int k=u+1;k<=19;k++){ //after leftmost 1 flip all other bits
						if(imm[k]==0+'0') imm[k]=1+'0';
						else if(imm[k]==1+'0') imm[k]=0+'0';
					}
				}
				if(a==false) break;
			}
			reverse(imm.begin(),imm.end());//reverse imm string to get binary form
		}
		else{ //if immediate is positive
			int i=0;
			for(;i<20;i++){ //calculates binary form of decimal (in reverse order)
				imm.push_back(temp%2 + '0');
				temp = temp/2;
				if(temp==1){
					imm.push_back(1+'0');
					i++;
					break;
				}
			}
			while(i<19){ //if imm. less than 20 bits
				imm.push_back(0+'0');
				i++;
			}
			reverse(imm.begin(),imm.end());
		}
		return imm;
	}else{
		return "rangeError"; //out_of_range error
	}
}

string Uformat(string line,string rd,string func,string imm,string in,int i,int count,vector<pair<string,string>> * regs){
	i++;
	string bintemp;
	string hex_imm;
	for(;i<line.length();i++){
		if(line[i] !=',' && !(isspace(line[i]))){
			// argument terminates with comma or space
			rd.push_back(line[i]);
		}
		else if(line[i] == ',') break;
	}
	string temp;
	for(;i<line.length();i++){
		if(!isspace(line[i]) && line[i]!=',') temp.push_back(line[i]);
	} //temp stores immediate
	if(temp[0] == '0' && temp[1] == 'x'){ //if imm. is in hex format
		if (temp.length()>2)  { //if valid immediate
			temp.erase(0,2);   //erase 0 and x 
		        hex_imm  = temp;
			reverse(temp.begin(),temp.end());
			while(temp.length()<5){
                             temp.append("0");
			}
			reverse(temp.begin(),temp.end());
			if(temp.length() ==5){
				for(int f=0;f<temp.length();f++){
					in.append(hex_to_bin(temp[f]));   //calculate binary of given hex digit    
				}
			}
		}
		for(int f=0;f<temp.length();f++){
			bintemp.append(hex_to_bin(temp[f]));   //calculate binary of given hex digit
		}
	}
	else{  
		imm = upperConstant(imm,temp,Opcode(func));//20-bit imm. appended
		bintemp.append(imm);
	}
	if(imm != "rangeError" )  {
		in.append(imm.substr(0,20));
	}else{
		cout<<"Immediate out of range in line "<<count<<endl;
		return "1";
	}
	if(reg(rd)!= "invalid") {
		in.append(reg(rd));
	}else{
		cout<<"Invalid identifier at destination register in line "<<count<<endl;
		return "1"; 
	}
	if(Opcode(func)!="invalid")  in.append(Opcode(func)); 
	upper_imm(reg(rd),hex_imm,regs);
	return in;
}
string Jformat(string line,string rd,string func,string imm,string in,int i,int count,
		vector<pair<int,string>> label,vector<pair<string,string>>* regs,string* PC,string* exec,int* stepper){
	//function that parses J-instruction to binary format
	bool next = true;
	i++;
	for (; i < line.length(); i++)
	{
		if (line[i] != ',' && !(isspace(line[i])))
		{ //second argument terminates with comma or space
			next = false;
			rd.push_back(line[i]);
		}
		else if (line[i] == ',')
			break;
	}
	i++;
	next = true;
	string target;
	for (; i < line.length(); i++)
	{ //target stores label name
		if (line[i] != ',' && !(isspace(line[i])))
		{
			next = false;
			target.push_back(line[i]);
		}
	}
	int p=0;
	/*if(!(stoi(target))){
	  imm = upperConstant(imm,target,Opcode(func));
	  }*/
	for (int m = 0; m < label.size(); m++)
	{
		if (label[m].second == target)
		{    //if label name present in vector of pairs label
			p=1;
			*stepper = label[m].first;
			imm = upperConstant(imm,to_string(4*(label[m].first-count)),Opcode(func));
			break;
		}
	}
	if(!p)    imm = upperConstant(imm,target,Opcode(func));
	if(*stepper !=1) *stepper = *stepper -count;
	jgen(func,reg(rd),imm,regs,PC,exec,&count,stepper);
	if (imm != "rangeError")
	{   //ignore last bit and extend sign
		imm.pop_back();
		reverse(imm.begin(),imm.end());	  
		if(imm[18] == 0+'0')      imm.push_back(0+'0');
		else if(imm[18] == 1+'0') imm.push_back(1+'0');
		reverse(imm.begin(),imm.end());	  
	}else{
		cout<<"Immediate value out of range in line "<<count<<endl;
		return "1";
	}
	in.append(imm.substr(0, 1));//imm[20]
	in.append(imm.substr(10, 10));//imm[10:1]
	in.append(imm.substr(9,1));//imm[11]
	in.append(imm.substr(1,8));//imm[19:12]
	if (reg(rd) != "invalid") {
		in.append(reg(rd));
	}else{
		cout<<"Invalid identifier at destination register in line "<<count<<endl;
		return "1"; 
	}
	in.append(Opcode(func));
	return in;
}
int main(int argc,char* argv[])
{
	vector<pair<string,string>> regs;
	vector<pair<string,string>> data;
	int didx=0;
	int base=10000;
	for(int f=0;f<40000;f++){
		string curr;
		curr.append(to_string(base+f));  //data.push_back(make_pair(d,"12345676"));
		reverse(curr.begin(),curr.end());
		curr.append("x0");
		reverse(curr.begin(),curr.end());
		data.push_back(make_pair(curr,"0x0"));
		curr.erase();
	}
	//for(int i=19890;i<20940;i++){
	//  cout<<"data["<< data[i].first <<"]="<<data[i].second<<endl;
	//}
	string PC = "0x00000000";
	bool load = false;
	string cmd;
	int idx=0;
	int stepper=1;
	string text[65536] = {"0x00"};
	// string data[]  
	static int end=0;
	vector<pair<int,string>> label; //A vector of pairs for storing label name,line
					//number pairs
	ifstream one("input.txt");    //open input.txt using file stream
				      //while file has not reached end of file
	int labelMatch =0;    //variable for storing line-numbers containing valid labels
	while(!one.eof()){     //loop  for storing instructions with valid labels
		string test;         // string to store line test
		string tfunc;        // test func string to verify input is label or operation
		getline(one,test);
		if(!test.empty()){
			labelMatch+=1;
			int k=0;
			bool empty = true;   // variable to check empty space after reading an argument 
			for(;k<test.length();k++){
				if(isspace(test[k]) && empty) k++; //if space before argument go to next char
				if(!isspace(test[k])){            
					empty = false;
					tfunc.push_back(test[k]); //push non empty argument 
				}
				else break;
			}  
			if(tfunc.find(':') < 100){ //If string is a label
				tfunc.pop_back();             //remove colon
				label.push_back(make_pair(labelMatch,tfunc));
				//make a pair of label name and line number of label
			}	
		}
		tfunc.erase(); //after each line execution erase func argument and instruction
		test.erase();
	}
	one.close();   //close input.txt
	ifstream step("input.txt");
	int step_count=0;
	while(cmd!="exit"){
		getline(cin,cmd);
		string temp;
		if(cmd == "load input.txt"){
			for(int i=0;i<32;i++){
				temp.push_back('x');
				temp.append(to_string(i));
				regs.push_back(make_pair(reg(temp),"0x0"));
				temp.erase();
			}
			cout<<endl;
		}
		else if(cmd == "run" ){

			string in;               //string for storing instruction in binary format 
						 //each argument of input stored as individual string                     
			ifstream inp("input.txt");
			string func;
			string rd;
			string rs1; 
			string rs2;
			string imm;
			int count=0;
			static int stop=0;
			while(!inp.eof()){  
				string exec;
				string line;
				if(stepper !=1){
					for(int w=1;w<=stepper;w++){
						getline(inp,line);
					}
				}else{
					getline(inp,line);
				}
				if(stepper>1) count = count+stepper;
				else count = count +1;
				stepper =1;
				if(!line.empty()){
					string check;
					string segment;
					bool space=true;
					for(int k=0;k<line.length();k++){
						if(isspace(line[k]) && space) k++;
						if(!isspace(line[k])){
							space = false;
							segment.push_back(line[k]);
						}
						else if(!space && isspace((line[k]))) break;
					}
					space = true;
					if(segment == ".data"){
						while(segment != ".text"){
							//       inp.ignore(0,'\n');
							segment.erase();
							getline(inp,line);
							for(int k=0;k<line.length();k++){
								if(isspace(line[k]) && space) k++;
								if(!isspace(line[k])){
									space = false;
									segment.push_back(line[k]);
								}
								else if(!space && isspace((line[k]))) break;
							}
						}
						getline(inp,line);
					}
					int i=0;
					for(int m=0;m<label.size();m++){
						if(count == label[m].first)  { //if line contains label
							string ignoreLabel;      
							// string to ignore labels by pushing to it instead of pushing to function argument
							bool before = true;    // variable to check space is before or after argument  
							for(;i<line.length();i++){
								if(isspace(line[i]) && before) i++;
								if(!isspace(line[i])){
									before = false;
									ignoreLabel.push_back(line[i]);//ignore that label argument
								}
								else break;
							}
							i++;
						}
					}
					space = true;
					for(;i<line.length();i++){
						if(isspace(line[i]) && space) i++;
						if(!isspace(line[i])){
							space = false;
							func.push_back(line[i]);
						}
						else break;
					}
					check = Opcode(func);
					if(check=="error"){
						string temp = func;
						func.erase();
						space = true;
						for(;i<line.length();i++){
							if(isspace(line[i]) && space) i++;
							if(!isspace(line[i])){
								space = false;
								func.push_back(line[i]);
							}
							else break;
						}
					}
					if(check == "0110011"){
						in = Rformat(line,rd,rs1,rs2,func,in,i,&regs);
					}
					else if(check == "0100011") {
						in = Sformat(line,rs1,rs2,func,imm,in,i,count,&regs,text,&data);
					}                                         
					else if (check=="0000011" || check == "1100111"){
						in= ILformat(line,rs1,func,imm,rd,in,i,count,text,&regs,&PC,&exec,&stepper,&data);
					}
					else if (check == "0010011"){
						in= IGformat(line,rs1,func,imm,rd,in,i,count,&regs);
					}
					else if(check == "1100011"){
						in = Bformat(line,rs1,rs2,func,imm,in,i,count,label,&regs,&PC,&exec,&stepper);
					}
					else if(check == "0110111"){
						in = Uformat(line,rd,func,imm,in,i,count,&regs);
					}else if(check == "1101111"){
						in = Jformat(line,rd,func,imm,in,i,count,label,&regs,&PC,&exec,&stepper);
					}
					if(in== "1")  {
						break;
					}
					//if( stop == 1) { //Any error reported as "1"
					//		cout<<"Execution terminated"<<endl;
					//		return 1;
					//	}
					string array;
					for(int i=0;i<in.length();i=i+4){
						string bin = in.substr(i,4);
						char c= conv(stoi(bin));
						array.push_back(c);
					}
					int it=0;
					for(int k=0;k<8;k=k+2){
						reverse(array.begin(),array.end());
						string slice;
						slice.append("0x");
						slice.append(array.substr(k+1,1));
						slice.append(array.substr(k,1));
						text[idx+it] = slice;
						reverse(array.begin(),array.end());
						it++;
					}  
					idx=idx+4;
					ofstream obj("output.hex",ios::app);
					if(obj.is_open()){
						obj<<array<<endl;
						obj.close();
					}
					cout<<"Executed "<<line<<" ; ";
					if(exec.empty()){
						cout<<"PC="<<PC<<endl;
						PC =  PCU(PC,"100");
					}
					else{
						cout<<"PC="<<PC<<endl;
						PC.erase();
						PC.append(exec);
						exec.erase();
					}
					array.erase();
					func.erase();
					rd.erase();
					rs1.erase();
					rs2.erase();
					in.erase();
					imm.erase();
				}
			}
			cout<<endl;
			inp.close();
		}
		else if(cmd == "regs" ){
			string temp;
			string bin;
			for(int i=0;i<32;i++){ 
				temp.push_back('x');
				temp.append(to_string(i));
				cout<<temp;
				if(i<=9) cout<<"   =  ";
				else cout<<"  =  ";
				cout<<regs[i].second<<endl;
				temp.erase();
			}
			cout<<endl;
		}
		if(cmd == "step"){
			if(step.eof()){
				end=1;
			}
			if(end==1){
				cout<<"nothing to step"<<endl;
			}
			else{
				string in;               //string for storing instruction in binary format 
				string func;
				string rd;
				string rs1; 
				string rs2;
				string imm;
				if(!step.eof()){  
					string exec;
					string line;
					if(stepper !=1){
						for(int w=1;w<=stepper;w++){
							getline(step,line);
						}
					}else{
						getline(step,line);
					}
					if(stepper>1) step_count = step_count+stepper;
					else step_count = step_count +1;
					stepper =1;
					if(!line.empty()){
						string check;
						int i=0;
						bool space=true;
						for(int m=0;m<label.size();m++){
							if(step_count == label[m].first)  { //if line contains label
								string ignoreLabel;      
								// string to ignore labels by pushing to it instead of pushing to function argument
								bool before = true;    // variable to check space is before or after argument  
								for(;i<line.length();i++){
									if(isspace(line[i]) && before) i++;
									if(!isspace(line[i])){
										before = false;
										ignoreLabel.push_back(line[i]);//ignore that label argument
									}
									else break;
								}
								i++;
							}
						}
						space = true;
						for(;i<line.length();i++){
							if(isspace(line[i]) && space) i++;
							if(!isspace(line[i])){
								space = false;
								func.push_back(line[i]);
							}
							else break;
						}
						check = Opcode(func);
						if(check=="error"){
							string temp = func;
							func.erase();
							space = true;
							for(;i<line.length();i++){
								if(isspace(line[i]) && space) i++;
								if(!isspace(line[i])){
									space = false;
									func.push_back(line[i]);
								}
								else break;
							}
						}
						if(check == "0110011"){
							in = Rformat(line,rd,rs1,rs2,func,in,i,&regs);
						}
						else if(check == "0100011") {
							in = Sformat(line,rs1,rs2,func,imm,in,i,step_count,&regs,text,&data);
						}                                         
						else if (check=="0000011" || check == "1100111"){
							in= ILformat(line,rs1,func,imm,rd,in,i,step_count,text,&regs,&PC,&exec,&stepper,&data);
						}
						else if (check == "0010011"){
							in= IGformat(line,rs1,func,imm,rd,in,i,step_count,&regs);
						}
						else if(check == "1100011"){
							in = Bformat(line,rs1,rs2,func,imm,in,i,step_count,label,&regs,&PC,&exec,&stepper);
						}
						else if(check == "0110111"){
							in = Uformat(line,rd,func,imm,in,i,step_count,&regs);
						}else if(check == "1101111"){
							in = Jformat(line,rd,func,imm,in,i,step_count,label,&regs,&PC,&exec,&stepper);
						}
						if(in== "1"){
							cout<<"Not stepped";
						}
						//if( stop == 1) { //Any error reported as "1"
						//		cout<<"Execution terminated"<<endl;
						//		return 1;
						//	}
						string array;
						for(int i=0;i<in.length();i=i+4){
							string bin = in.substr(i,4);
							char c= conv(stoi(bin));
							array.push_back(c);
						}
						int it=0;
						for(int k=0;k<8;k=k+2){
							reverse(array.begin(),array.end());
							string slice;
							slice.append("0x");
							slice.append(array.substr(k+1,1));
							slice.append(array.substr(k,1));
							text[idx+it] = slice;
							reverse(array.begin(),array.end());
							it++;
						}  
						idx=idx+4;
						ofstream obj("output.hex",ios::app);
						if(obj.is_open()){
							obj<<array<<endl;
							obj.close();
						}
						cout<<"Executed "<<line<<" ; ";
						if(exec.empty()){
							cout<<"PC="<<PC<<endl;
							PC =  PCU(PC,"100");
						}
						else{
							cout<<"PC="<<PC<<endl;
							PC.erase();
							PC.append(exec);
							exec.erase();
						}
						array.erase();
						func.erase();
						rd.erase();
						rs1.erase();
						rs2.erase();
						in.erase();
						imm.erase();
					}
				}
				cout<<endl;
			}
		}
	}
	step.close();
	if(cmd == "exit"){
		cout<<"Exited the simulator"<<endl;
	}
	return 0;
}

