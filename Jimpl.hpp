



void jgen(string func,string rd, string imm,vector<pair<string,string>>*regs,string* PC,string* exec,int *count,int * stepper){
    int a=0;
    string temp;
    string adder;
    for(int i=4;i>=0;i--){
    int b=0;
      b+=(rd[i]-'0');
      for(int k=1;k<5-i;k++){
	      b*=2;
      }
      a=a+b;
    }
   regs->at(a).second.erase();
   regs->at(a).second.append(*PC);
         *exec = PCU(*PC,imm);
}

