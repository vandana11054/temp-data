

void upper_imm(string rd,string imm,vector<pair<string,string>> *regs){
int  a=0;
    for(int i=4;i>=0;i--){
    int b=0;
      b+=(rd[i]-'0');
      for(int k=1;k<5-i;k++){
              b*=2;
      }
      a=a+b;
    }
 if(imm.length() <= 2){
    reverse(imm.begin(),imm.end());
    for (int i = imm.length(); i < 2; i++)
    { 
      imm.push_back('0');
    }
    reverse(imm.begin(),imm.end());
    imm.append("000");
    reverse(imm.begin(),imm.end());
    imm.append("x0");
    reverse(imm.begin(),imm.end());
	regs->at(a).second.erase();
	regs->at(a).second.append(imm);
 }
 else{
       cout<<"error out of bounds ";
 }
}
