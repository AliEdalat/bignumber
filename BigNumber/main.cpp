#include <iostream>
#include "Bignum.h"
using namespace std;

int main(){
    Bignum n1("-123.1");
    Bignum n2(98.12);

    cout<<n1<<" "<<n2<<endl;

    Bignum n3("-00123.0010");
    Bignum n4=n3;
    n4=Bignum("1");
    Bignum n5("99999999999999999999999999999999999999999999");
    //cout<<n3<<endl;
    //cout<<n4<<endl;
    cout<<n3[0]<<n3[1]<<n3[2]<<n3[-1]<<endl;
    cout<<n1[0]<<n1[1]<<n1[2]<<n1[3]<<n1[-1]<<n1[-2]<<n1[-3]<<endl;
    cout<<n1+n4<<endl;
    cout<< (n3==n4) <<endl;
    cout<< (n5 < n5) <<endl;
    cout<< n5+n4<<endl;
    cout<< (n4+=n4) <<endl;
    cout<<12+n3<<endl;
    cout<<n3+12<<endl;
    cout<<(n3++)+12<<endl;
    cout<<++n3<<endl;
    cin>>n3;
    //cout<<n1<<endl;
    //cout<<n2<<endl;
    //cout<<n3<<endl;
    Bignum n7;
    n7=-n5;
    cout<<n7<<endl;
    cin>>n1[0];
    cout<<n1<<endl;
    cout<<n1+n3<<endl;
    cout<<n1<<endl;
    cout<<n1[0]<<n1[1]<<n1[2]<<n1[3]<<n1[-1]<<n1[-2]<<n1[-3]<<endl;

    cout<<12+n3<<endl;
    cout<<n3+12<<endl;
    double d=1.123454;
    Bignum ali(d);
    cout<<ali<<endl;
    cout<< (ali==d)<<endl;
    cout<<(d+=ali)<<endl;
    cout<<(ali+=1)<<endl;
    cout<<d+ali+n4<<endl;
    Bignum o("-00000.0000");
    cout<<-o<<endl;
    cout<<(-o)+Bignum(1)<<endl;
    int ppp=n1[0];
    cout<<ppp<<endl;
    return 0;
}
