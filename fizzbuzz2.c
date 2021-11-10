main(i,f,b){char*p="%d\n\0fizzbuzz\n";for(;i<101;){f=1>i%3;b=1>i%5;p[8]=88*b+10;p[9]='u'*b;printf(p+b*!f*8+f*4,i++);}}
// gcc34 -Wall -fwritable-strings fizzbuzz2.c -o fizzbuzz
