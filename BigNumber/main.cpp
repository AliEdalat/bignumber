#include <iostream>
#include "Bignum.h"
using namespace std;

int main(){
    Bignum n1("-123.1");
    Bignum n2(98.12);

    cout<<n1<<" "<<n2<<endl;

    Bignum n3("-00123.0010");
    Bignum n4=n3;
    n4=Bignum("-900");
    //cout<<n3<<endl;
    //cout<<n4<<endl;
    cout<<n3[0]<<n3[1]<<n3[2]<<n3[-1]<<endl;
    cout<<n1[0]<<n1[1]<<n1[2]<<n1[3]<<n1[-1]<<n1[-2]<<n1[-3]<<endl;
    cout<<n1+n4<<endl;
    cout<< (n3==n4) <<endl;
    /*cin>>n3;
    cout<<n1<<endl;
    cout<<n2<<endl;
    cout<<n3<<endl;
    Bignum n4;
    n4=-n3;
    cout<<n4<<endl;
    cin>>n1[0];
    cout<<n1<<endl;
    //cout<<n1+n3<<endl;

    cout<<n1[0]<<n1[1]<<n1[2]<<n1[3]<<n1[-1]<<n1[-2]<<n1[-3]<<endl;

    /*cout<<12+n3<<endl;
    cout<<n3+12<<endl;
    */
    return 0;
}
