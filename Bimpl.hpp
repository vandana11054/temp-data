void bgen(string func,string rs1,string rs2,string imm,vector<pair<string,string>>*regs,string* PC,string* exec,int* count,int* stepper){
    int a=0;
    string temp1;
    string temp2;
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
   if(temp1.length()<16){
         reverse(temp1.begin(),temp1.end());
         while(temp1.length()<16) temp1.push_back('0'); 
         reverse(temp1.begin(),temp1.end());
   }
   if(temp2.length()<16){
         reverse(temp2.begin(),temp2.end());
         while(temp2.length()<16) temp2.push_back('0'); 
         reverse(temp2.begin(),temp2.end());
   }
   if(temp1==temp2 && func=="beq"){
         *exec = PCU(*PC,imm);
         if(*stepper !=1) *stepper = *stepper-*count;
   }else if(temp1!=temp2 && func == "beq"){
          *stepper =1;
   }
   if(temp1!=temp2 && func=="bne"){
         *exec = PCU(*PC,imm);
         if(*stepper !=1) *stepper = *stepper-*count;
   }else if(temp1==temp2 && func == "bne"){
          *stepper =1;
   }
  if( !(hex_cmp(temp1,temp2))  && func=="blt" ){
         *exec = PCU(*PC,imm);
         if(*stepper !=1) *stepper = *stepper-*count;
   }else if(hex_cmp(temp1,temp2) && func == "blt"){
          *stepper =1;
   }
   if(func=="bge" && hex_cmp(temp1,temp2)){
         *exec = PCU(*PC,imm);
         if(*stepper !=1) *stepper = *stepper-*count;
   }else if(!(hex_cmp(temp1,temp2)) && func == "bge"){
          *stepper =1;
   }
  if(func=="bltu" && !(uhex_cmp(temp1,temp2))){
         *exec = PCU(*PC,imm);
         if(*stepper !=1) *stepper = *stepper-*count;
   }else if(uhex_cmp(temp1,temp2) && func == "bltu"){
          *stepper =1;
   }
  if(func=="bgeu" && (uhex_cmp(temp1,temp2))){
         *exec = PCU(*PC,imm);
         if(*stepper !=1) *stepper = *stepper-*count;
   }else if(!(uhex_cmp(temp1,temp2)) && func == "bgeu"){
          *stepper =1;
   }
}
