#include <iostream>
#include <map>
#include <set>
#include <string>
#include <cstring>
#include <string.h>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <stack>
#include <vector>
#include <queue>
#include <sstream>
using namespace std;
typedef long long ll;

struct BASE64{
    char input[2005],output[2005];
    int inlen,outlen;
    void getinput(){cin.getline(input,2000);}   //deal with ' ';
    void printout(){printf("%s\n",output);}
    char table_64[70]={
        'A','B','C','D','E','F','G','H','I','J',
        'K','L','M','N','O','P','Q','R','S','T',
        'U','V','W','X','Y','Z','a','b','c','d',
        'e','f','g','h','i','j','k','l','m','n',
        'o','p','q','r','s','t','u','v','w','x',
        'y','z','0','1','2','3','4','5','6','7',
        '8','9','+','/','=',    //add '='  useless
    };
    char inverse[130]={
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,62,0,0,0,63,52,53,
        54,55,56,57,58,59,60,61,0,0,
        0,61,0,0,0,0,1,2,3,4,
        5,6,7,8,9,10,11,12,13,14,
        15,16,17,18,19,20,21,22,23,24,
        25,0,0,0,0,0,0,26,27,28,
        29,30,31,32,33,34,35,36,37,38,
        39,40,41,42,43,44,45,46,47,48,
        49,50,51,0,0,0,0,0,
    };

    void encode(){
        inlen=strlen(input);
        outlen=0;
        for(int i=0;i+2<inlen;i+=3){
            output[outlen++]=table_64[(input[i]>>2)];
            output[outlen++]=table_64[(((input[i]&0x03)<<4)|(input[i+1]>>4))];
            output[outlen++]=table_64[(((input[i+1]&0x0f)<<2)|(input[i+2]>>6))];
            output[outlen++]=table_64[input[i+2]&0x3f];
        }
        int p=0;
        if(inlen%3==1){
            p=inlen-1;
            output[outlen++]=table_64[(input[p]>>2)];
            output[outlen++]=table_64[(((input[p]&0x03)<<4)|0)];//
            output[outlen++]='=';
            output[outlen++]='=';
        }else if(inlen%3==2){
            p=inlen-2;
            output[outlen++]=table_64[(input[p]>>2)];
            output[outlen++]=table_64[(((input[p]&0x03)<<4)|(input[p+1]>>4))];
            output[outlen++]=table_64[(((input[p+1]&0x0f)<<2)|0)];
            output[outlen++]='=';
        }
        output[outlen]='\0';
    }
    void decode(){
        inlen=strlen(input);
        outlen=0;
        for(int i=0;i+7<inlen;i+=4){
            output[outlen++]=((inverse[input[i]]&0x3f)<<2)|((inverse[input[i+1]]&0x3f)>>4);
            output[outlen++]=((inverse[input[i+1]]&0x3f)<<4)|((inverse[input[i+2]]&0x3f)>>2);
            output[outlen++]=((inverse[input[i+2]]&0x3f)<<6)|((inverse[input[i+3]]&0x3f));
        }
        int p=inlen-4;
        if(input[inlen-2]=='='){
            output[outlen++]=((inverse[input[p]]&0x3f)<<2)|((inverse[input[p+1]]&0x3f)>>4);
        }else if(input[inlen-1]=='='){
            output[outlen++]=((inverse[input[p]]&0x3f)<<2)|((inverse[input[p+1]]&0x3f)>>4);
            output[outlen++]=((inverse[input[p+1]]&0x3f)<<4)|((inverse[input[p+2]]&0x3f)>>2);
        }else{
            output[outlen++]=((inverse[input[p]]&0x3f)<<2)|((inverse[input[p+1]]&0x3f)>>4);
            output[outlen++]=((inverse[input[p+1]]&0x3f)<<4)|((inverse[input[p+2]]&0x3f)>>2);
            output[outlen++]=((inverse[input[p+2]]&0x3f)<<6);
        }
        output[outlen]='\0';
    }
};
BASE64 ca;
int main(){
    ca.getinput();
    ca.encode();
    ca.printout();
    cout <<endl;
    ca.decode();
    ca.printout();
    return 0;
}
