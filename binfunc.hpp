#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

string binadd(string a,string b){
if(a.length() <b.length()){
      swap(a,b);
}
string res;
      int q=0;
int k=a.length()-b.length()-1;
     reverse(b.begin(),b.end());
for(;k>=0;k--){
     b.push_back(b[b.length()-1]);
}
      reverse(b.begin(),b.end());

int i= a.length()-1;
for(;i>=0;i--){
      int p = (a[i]-'0')+(b[i]-'0')+q;
      if(p==2) {
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
if(q)
{
      res.push_back(q+'0');
}
      reverse(res.begin(),res.end());
      if(res.length()>64){
          reverse(res.begin(),res.end());
	  while(res.length()>64) res.pop_back();
          reverse(res.begin(),res.end());
      }
return res;
}

string binand(string a,string b){
if(a.length() < b.length()){
      swap(a,b);
}
string res;
int k=a.length()-b.length()-1;
     reverse(b.begin(),b.end());
for(;k>=0;k--){
     b.push_back('0');
}
 reverse(b.begin(),b.end());
 int i= a.length()-1;
for(;i>=0;i--){
    if(a[i]==1+'0' && b[i]==1+'0'){
    res.push_back(1+'0');
    }
    else{
    res.push_back(0+'0');
    }
}
 reverse(res.begin(),res.end());
 return res;
}

string binxor(string a,string b){
if(a.length() <b.length()){
      swap(a,b);
}
string res;
int k=a.length()-b.length()-1;
     reverse(b.begin(),b.end());
for(;k>=0;k--){
     b.push_back(b[b.length()-1]);
}
 reverse(b.begin(),b.end());
 int i= a.length()-1;
for(;i>=0;i--){
    if(a[i]==1+'0' && b[i]==1+'0'||a[i]==0+'0' && b[i]==0+'0'){
    res.push_back(0+'0');
    }
    else{
    res.push_back(1+'0');
 }
}
 reverse(res.begin(),res.end());
 return res;
}

string binor(string a,string b){
if(a.length() <b.length()){
      swap(a,b);
}
string res;
int k=a.length()-b.length()-1;
     reverse(b.begin(),b.end());
for(;k>=0;k--){
     b.push_back('0');
}
      reverse(b.begin(),b.end());
 int i= a.length()-1;
for(;i>=0;i--){
    if(a[i]==1+'0' || b[i]==1+'0'){
    res.push_back(1+'0');
    }
    else{
    res.push_back(0+'0');
 }
}
 reverse(res.begin(),res.end());
return res;
}
string INT_Str(int arr[], int size)
{
    string str;
    for (int i = 0; i < size; i++)
    {
        str += (arr[i] + '0');
    }
    return str;
}
int* str_int(string arr)
{     
    int * num = new int [arr.length()];
    for (int i = 0; i < arr.length(); i++)
    {
        num[i]= (arr[i] - '0');

    }
    return num;
}


long int unsigneddecimal(int* num,int size){
    long int sum=0;
    int i=size-1;
    int j=size-1;
    for (; i >=0; i--)
     {   
        int k=1;
        for(int a=0;a<j-i;a++){
        k=k*2;
        }
        sum += num[i] * k; 
     }
    return sum;
}


string binsll(string a,string b,string func){
string b2;
if (b.length()<64)
{     reverse(b.begin(),b.end());
    for ( int i = b.length(); i <64 ; i++)
    {
         b.push_back('0');
    }
    reverse(b.begin(),b.end());
}
int j=58;
for( int i=5 ; i>=0 ; i--,j++){
    b2+=b[j];
}
int *ptr;
ptr=str_int(b2);
 int y=unsigneddecimal(ptr,b2.length());
for (int i = 0; i < y; i++)
{
    a.push_back('0');
}
if (a.length()>64)
{
    reverse(a.begin(),a.end());
    while (a.length()>64)
    {
        a.pop_back();
    }
    reverse(a.begin(),a.end());
}
else if(a.length()<64)
{
    reverse(a.begin(),a.end());
    while (a.length()<64)
    {
        a.push_back(a[a.length()-1]);
    }
    reverse(a.begin(),a.end());
}
return a;
 }

string binsrl(string a,string b,string func){
string b2;
if (b.length()<64)
{     reverse(b.begin(),b.end());
    for ( int i = b.length(); i <64 ; i++)
    {
        b.push_back('0');
    }
    reverse(b.begin(),b.end());
}
int j=58;
for( int i=5 ; i>=0 ; i--,j++){
    b2+=b[j];
}
int *ptr;
ptr=str_int(b2);
 int y=unsigneddecimal(ptr,b2.length());
for (int i = 0; i < y; i++)
{
    a.pop_back();
}
 if(a.length()<64)
{
    reverse(a.begin(),a.end());
    while (a.length()<64)
    {
        a.push_back('0');
    }
    reverse(a.begin(),a.end());
}
return a;
}

string binsra(string a,string b,string func){
string b2;
if (b.length()<64)
{     reverse(b.begin(),b.end());
    for ( int i = b.length(); i <64 ; i++)
    {
        b.push_back('0');
    }
    reverse(b.begin(),b.end());
}
int j=58;
for( int i=5 ; i>=0 ; i--,j++){
    b2+=b[j];
}
int *ptr;
ptr=str_int(b2);
 int y=unsigneddecimal(ptr,b2.length());
for (int i = 0; i < y; i++)
{
    a.pop_back();
}
 if(a.length()<64)
{
    reverse(a.begin(),a.end());
    while (a.length()<64)
    {
        a.push_back(a[a.length()-1]);
    }
    reverse(a.begin(),a.end());
    
}
return a;
}

int hex_cmp(string a,string b){
if(a==b) {
    return 1;
    }
if((48<=a[0]&&a[0]<=55)&&(97<=b[0]&&b[0]<=102||b[0]==56||b[0]==57)){
    return 1;
}
else if((48<=b[0]&&b[0]<=55)&&(97<=a[0]&&a[0]<=102||a[0]==56||a[0]==57)){
    return 0;
}
else{
   for (int i = 0; i <a.length(); i++)
  {
    if (a[i]<b[i])
    { 
        return 0;
    }
    if (a[i]>b[i])
    {   
        return 1;
    }
  }
}
return 0;
}

int uhex_cmp(string a,string b){
if(a==b) return 1;
   for (int i = 0; i <a.length(); i++)
  {
    if (a[i]<b[i])
    { 
        return 0;
    }
    if (a[i]>b[i])
    {   
        return 1;
    }
  }
   return 0;
}
