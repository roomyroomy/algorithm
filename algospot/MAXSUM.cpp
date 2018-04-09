#include <stdio.h>
#include <iostream>
#define k(a) scanf("%d",&a);
int t,n,p,m,a,i;
int main(){k(t)while(t--){k(n)for(i=m=p=0;i<n;i++){k(a)p=std::max(p,0)+a;m=std::max(m, p);}printf("%d\n", m);}}
