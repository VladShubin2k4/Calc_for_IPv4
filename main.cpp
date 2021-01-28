#include <iostream>
//#include <cstdio>
using namespace std;

int transfer(int byte,short radix){
  int res=0, k=1;
  for(short i=0;byte!=0; ++i){res+=(byte%radix)*k;k*=10;byte/=radix;}
  return res;
}
int formout(int out){
   int radix=0,tmp=out;
   while(tmp>0){tmp/=10; ++radix;}
   for(int i=radix; i<8; ++i) cout<<0;
   return out;
}
int fastpow(int a, int n){
  if(n==0) return 1;
  if(n%2==1) return (a*fastpow(a,n-1));
  int tmp=fastpow(a,n/2);
  return (tmp*tmp);
}
void Info(int* byte){
    cout<<"In BIN(2): ";
    for(short i=0; i<4; ++i){cout<<formout(transfer(byte[i],2));if(i!=3) cout<<".";}
    cout.unsetf(ios::dec); cout.setf(ios::hex);
    cout<<"\nIn HEX(16): ";
    for(short i=0; i<4; ++i){cout<<byte[i]; if(i!=3) cout<<"."; }
    cout.unsetf(ios::hex); cout.setf(ios::oct);
    cout<<"\nIn OCT(8): ";
    for(short i=0; i<4; ++i){cout<<byte[i]; if(i!=3) cout<<".";}
    cout.unsetf(ios::oct); cout.setf(ios::dec);
    cout<<"\nCIDR?\n";
}
void CIDR(int* byte){
    short cidr,ip[32]={};
    cin>>cidr;
    for(short i=0; i<4; ++i){
        for(short j=i*8; j<8*(i+1); ++j){
            int octet=transfer(byte[i],2)%fastpow(10,8-(j%8)),div=fastpow(10,7-(j%8));
            ip[j]=octet/div;
        }
    }
    cout<<"Net ID = ";
    for(short i=0; i<cidr; ++i){
        if(i%8==0 && i!=0) cout<<'.';
        cout<<ip[i];
    }
    cout<<"\nHost ID = ";
    for(short i=cidr; i<32; ++i){
        if(i%8==0) cout<<'.';
        cout<<ip[i];
    }
    cout<<"\n";
}
void ClassOfIP(int* byte){
    if(byte[0]<128){
        if(byte[0]==10 && byte[0]<=126 && byte[1]<256 && byte[2]<256 && byte[3]<256) cout<<"\n!Common adress!\n";
        else cout<<"\nUnic adress\n";
        cout<<"\nA class:\n\tNet ID = "<<formout(transfer(byte[0],2))<<"\n";
        cout<<"\tHost ID = ";
        for(short i=1; i<4; ++i){
            cout<<formout(transfer(byte[i],2));
            if(i!=3) cout<<".";
        }
    }else if(byte[0]<192){
        if(byte[0]==172 && byte[1]<32 && byte[1]>15 && byte[2]<256 && byte[3]<256) cout<<"\n!Common adress!\n";
        else cout<<"\nUnic adress\n";
        cout<<"\nB class:\n\tNet ID = "<<formout(transfer(byte[0],2))<<"."<<formout(transfer(byte[1],2))<<"\n";
        cout<<"\tHost ID = "<<formout(transfer(byte[2],2))<<"."<<formout(transfer(byte[3],2));
    }else if(byte[0]<224){
        if(byte[0]==192 && byte[1]==168 && byte[2]<256 && byte[3]<256) cout<<"\n!Common adress!\n";
        else cout<<"\nUnic adress\n";
        cout<<"\nC class:\n\tNet ID = ";
        for(short i=0; i<3; ++i){
            cout<<formout(transfer(byte[i],2));
            if(i!=2) cout<<".";
        }
        cout<<"\n\tHost ID = "<<formout(transfer(byte[3],2));
    }else cout<<"\tD/E class";
    cout<<"\n";
}

int main(){
    //freopen("ip-res.txt","w",stdout);
    ios::sync_with_stdio(false);
    int byte[4];
    char dot, cmd;
    for(short i=0; i<4; ++i){cin>>byte[i];if(i!=3) cin>>dot;}
    Info(byte);
    cin>>cmd;
    if(cmd=='y') CIDR(byte);
    else ClassOfIP(byte);
    cin.get();cin.get();
    return 0;
}
