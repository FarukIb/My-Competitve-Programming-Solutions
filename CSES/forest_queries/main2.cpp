#include <iostream>
#include <bits/stdc++.h>
using namespace std;

typedef long long lol;
typedef pair<int,int> pii;

const int maxn=2e5+1;
int n;
int seg[maxn*4];

int niz[maxn];
/*
void build(int l,int r, int idx){
if(l==r){
seg[idx]=niz[l];
return;
}
int mid=(l+r)/2;
build(l,mid,idx*2);
build(mid+1,r,idx*2+1);
seg[idx]=seg[idx*2]+seg[idx*2+1];
}*/

int query(int l,int r,int L, int R,int idx){
    if(l>R||r<L) return 0;
    if(l>=L and r<=R) return seg[idx];
    int mid=(l+r)/2;
    return query(l,mid,L,R,idx*2)+query(mid+1,r,L,R,idx*2+1);
}

int query(int l, int r) {
    return query(0, n - 1, l, r, 1);
}

void mod(int l,int r,int idx,int i,int val){
    if(l>i||r<i) return;
    if(l==i and r==i){
        seg[idx]+=val;
        return;
    }
    int mid=(l+r)/2;
    mod(l,mid,idx*2,i,val);
    mod(mid+1,r,idx*2+1,i,val);
    seg[idx]=seg[idx*2]+seg[idx*2+1];

}
void mod(int i,int val){
    mod(0,n-1,1,i,val);
}

int main(int argc, char** argv) {
    int q; cin>>n>>q;

    vector<int> a(n+1),p(n+1);
    for(int i=1;i<n+1;i++){
        cin>>a[i];
    }

    while(q--){
        int h; cin>>h;
        if(h==1){
            int d,b,u; cin>>d>>b>>u;
            mod(d-1,u);
            if(b!=n) mod(b,-u);
        }
        else{
            int z; cin>>z;
            cout<<a[z]+query(0,z-1)<<endl;
        }

    }




    return 0;
}