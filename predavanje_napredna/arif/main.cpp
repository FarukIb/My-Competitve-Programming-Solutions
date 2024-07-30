#include <iostream>

using namespace std;

long long seg[1000005],a[1000005];
long long n,q;

void update(long long idx, long long l, long long r, long long ind2, long long s){
    if(r==l){
        seg[idx]=seg[idx]+s;
        return ;
    }
    seg[idx]=seg[idx]+s;
    if (ind2 <= (l + r) / 2)
        update(idx*2,l,(l+r)/2,ind2,s);
    else
        update(idx*2+1,(l+r)/2+1,r,ind2,s);
}
long long query(long long idx, long long l, long long r, long long l1, long long r1){
    if(l1>r || r1<l){
        return 0;
    }
    if(l1<=l && r<=r1){
        return seg[idx];
    }
   return query(idx*2,l,(l+r)/2,l1,r1)+query(idx*2+1,(l+r)/2+1,r,l1,r1);
}
int main(){
    cin >> n >> q;
    for(long long i = 0;i<n;i++){
        cin >> a[i];
    }
    while(q--){
        long long t1;
        cin >> t1;
        if(t1==1){
            long long t2,t3,t4;
            cin >> t2 >> t3 >> t4;
            t2--, t3--;
            update(1,0,n-1,t2-1,-t4);
            update(1,0,n-1,t3,t4);
        }else if(t1==2){
            long long t2;
            cin >> t2;
            t2--;
            cout << query(1,0,n-1,t2,n-1)+a[t2] << endl;
        }
    }
   
}