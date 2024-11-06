



void store(string func,string rs2,string rs1,string imm,vector<pair<string,string>> * regs,string* text,vector<pair<string,string>> * data){
    int a=0;
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
   value= regs->at(a).second;
   reverse(value.begin(),value.end());
   value.pop_back();
   value.pop_back();
   if(value.length()<16){
      while(value.length()<16) value.push_back('0');
   }
   reverse(value.begin(),value.end());
	string src;
        for(int k=0;k<temp.length();k++){
              src.append(hex_to_bin(temp[k]));
	}
	if(imm.length()<64){
              reverse(imm.begin(),imm.end());
	      while(imm.length()<64){
                 imm.push_back(imm[imm.length()-1]);
	      }
              reverse(imm.begin(),imm.end());
	}
	string in;
        in = binadd(imm,src);
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
      if(func == "sd"){
	int p=14;
        for(int z=0;z<=7;z++){
		if(dec<0) break;
             text[dec+z] = "0x";
	     text[dec+z].append(value.substr(p,2));
	     p-=2;
	}
      }
      if(func == "sw"){
	int p=14;
        for(int z=0;z<=3;z++){
		if(dec<0) break;
             text[dec+z] = "0x";
	     text[dec+z].append(value.substr(p,2));
	     p-=2;
	}
      }
      if(func == "sb"){
	int p=14;
        for(;;){
		if(dec<0) break;
             text[dec] = "0x";
	     text[dec].append(value.substr(p,2));
	     p-=2;
	     break;
	}
}
}
