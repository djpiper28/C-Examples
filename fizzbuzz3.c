#define p printf
main(i,f){for(;i<101;i++){f=1>i%3||1>i%5;if(f){if(1>i%3)p("fizz");if(1>i%5)p("buzz");}else{p("%d",i);}p("\n");}}
