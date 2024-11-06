



void store(string func,string rs2,string rs1,string imm,vector<pair<string,string>> * regs,string* text,vector<pair<string,string>> * data){
int a = 0;
string temp;
string adder;
string value;
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
b+=(rs2[i]-'0');
for(int k=1;k<5-i;k++){
      b*=2;
}
a=a+b;
}
value = regs->at(a).second;
reverse(value.begin(),value.end());
value.pop_back();
value.pop_back();
if(value.length()<16){
while(value.length()<16)   value.push_back('0');
}
reverse(value.begin(),value.end());
string src;
for(int k=0;k<temp.length();k++){
      src.append(hex_to_bin(temp[k]));
}
if(imm.length()< src.length()){
      reverse(imm.begin(),imm.end());
    while(imm.length()<src.length()){
	 imm.push_back(imm[imm.length()-1]);
      }
      reverse(imm.begin(),imm.end());
}
string in;
in = binadd(imm,src);
string input;
			for(int i=0;i<in.length();i=i+4){
				string bin = in.substr(i,4);
				char c= conv(stoi(bin));
				input.push_back(c);
					}
cout<<"Input value at store is "<<input<<endl;
int dec = stoi(input);
reverse(input.begin(),input.end());
input.append("x0");
reverse(input.begin(),input.end());
if(func == "sd"){
int p=14;
for(int m=0;m<50000;m++){
if(data->at(m).first == input){	     
for(int z=0;z<=7;z++){
	if(dec<0) break;
     data->at(m+z).second.erase();
     data->at(m+z).second.append("0x");
     data->at(m+z).second.append(value.substr(p,2));
     p-=2;
}
break;
}
}
}
if(func == "sw"){
int p=14;
for(int m=0;m<50000;m++){
if(data->at(m).first == input){	     
for(int z=0;z<=3;z++){
	if(dec<0) break;
     data->at(m+z).second.erase();
     data->at(m+z).second.append("0x");
     data->at(m+z).second.append(value.substr(p,2));
     p-=2;
}
break;
}
}
}
if(func == "sh"){
int p=14;
for(int m=0;m<50000;m++){
if(data->at(m).first == input){	     
for(int z=0;z<=1;z++){
	if(dec<0) break;
     data->at(m+z).second.erase();
     data->at(m+z).second.append("0x");
     data->at(m+z).second.append(value.substr(p,2));
     p-=2;
}
break;
}
}
}
if(func == "sb"){
int p=14;
for(int m=0;m<50000;m++){
if(data->at(m).first == input){	     
for(;;){
	if(dec<0) break;
     data->at(m).second.erase();
     data->at(m).second.append("0x");
     data->at(m).second.append(value.substr(p,2));
     p-=2;
     break;
}
break;
}
}
}
for(int i= 9000;i<9020;i++){
       cout<<"  "<<data->at(i).first<<" = "<<data->at(i).second<<endl;
}
}
