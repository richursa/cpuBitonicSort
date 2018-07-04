#include<iostream>
#include<omp.h>
using namespace std;

void ascendingSwap(int index1 , int index2 , int *ar)
{
  if(ar[index2] < ar[index1])
  {
      int temp = ar[index2];
      ar[index2] = ar[index1];
      ar[index1] = temp;
  }
}
void decendingSwap(int index1 , int index2 , int *ar)
{
  if(ar[index1] < ar[index2])
  {
      int temp = ar[index2];
      ar[index2] = ar[index1];
      ar[index1] = temp;
  }
}
    void bitonicSortFromBitonicSequence( int startIndex ,int lastIndex, int dir , int *ar )
    {
        if(dir == 1)
        {
            int counter = 0;
            int noOfElements = lastIndex - startIndex + 1;
            for(int j = noOfElements/2;j>0;j = j/2)
            {   counter =0;
                for(int i = startIndex ; i +j <= lastIndex ; i++)
                {
                        if(counter < j)
                        {
                            ascendingSwap(i,i+j,ar);
                            counter++;

                        }
                        else 
                        {
                            counter =0;
                            i = i+ j-1;
                            
                        }
                }
            }
        }
        else
        {
            int counter = 0;
            int noOfElements = lastIndex - startIndex + 1;
            for(int j = noOfElements/2;j>0;j = j/2)
            {   counter =0;
                for(int i = startIndex ; i <= (lastIndex-j) ; i++)
                {
                        if(counter < j)
                        {
                            decendingSwap(i,i+j,ar);
                            counter++;

                        }
                        else 
                        {
                            counter =0;
                            i = i+ j-1;
                            
                        }
                }
            }
        }
    
    }
void bitonicSequenceGenerator(int startIndex , int lastIndex , int *ar)
{
    int noOfElements = lastIndex - startIndex +1;
    int counter =0;
      for(int j = 2;j<=noOfElements;j = j*2)
            {   
                counter =0;
                #pragma omp parallel for
                for(int i=0;i<noOfElements;i=i+j)
                {
                 if(((i/j)%2) ==0)
                 {
                     bitonicSortFromBitonicSequence(i,i+j-1,1,ar);
                     counter++;
                 }   
                 else
                 {
                     bitonicSortFromBitonicSequence(i,i+j-1,0,ar);
                     counter++;
                 }
                }
            }
}
int main()
{
    omp_set_dynamic(0);
    omp_set_num_threads(3);
    int n;
    cin>>n;
    int *ar = new int[n];
    for(int i=0;i<n;i++)
    {
        cin>>ar[i];
    }
    bitonicSequenceGenerator(0,n-1,ar);
    for(int i=0;i<n;i++)
    {
        cout<<ar[i]<<"\n";
    }

}
