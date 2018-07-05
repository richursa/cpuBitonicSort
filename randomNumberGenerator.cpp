#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<iostream>
using namespace std;
int main () {
   int i, n;
   time_t t;
   
   cin>>n;
   
   /* Intializes random number generator */
   srand((unsigned) time(&t));

   /* Print 5 random numbers from 0 to 49 */
   cout<<n<<"\n";
   for( i = 0 ; i < n ; i++ ) {
       cout<<rand()<<"\n";
   }
   
   return(0);
}