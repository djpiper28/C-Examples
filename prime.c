main(f,n,i){char s[9];gets(s);for(n=i=atoi(s);f&&i-->2;)f=n%i;f=f&&n-1;puts("non-prime"+f*4);}
//main(a,v,p){char i[9];gets(i);for(v=p=atoi(i);a&&p>2;a=v%--p);a=a&&!v-1;puts("non-prime"+a*4);}
