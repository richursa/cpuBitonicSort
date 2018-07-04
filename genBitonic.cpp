#include<iostream>                                                                              //for std::cout ,std::cin
#include<omp.h>                                                                                 
using namespace std;

void ascendingSwap(int index1 , int index2 , int *ar)                                           //swap two values such that they appear in ascending order in the array
{
  if(ar[index2] < ar[index1])
  {
      int temp = ar[index2];
      ar[index2] = ar[index1];
      ar[index1] = temp;
  }
}
void decendingSwap(int index1 , int index2 , int *ar)                                           //swap two values such that they appear in decending order in the array
{
  if(ar[index1] < ar[index2])
  {
      int temp = ar[index2];
      ar[index2] = ar[index1];
      ar[index1] = temp;
  }
}
    void bitonicSortFromBitonicSequence( int startIndex ,int lastIndex, int dir , int *ar )     //form a increaseing or decreasing array when a bitonic input is given to the function
    {
        if(dir == 1)
        {
            int counter = 0;                                                                    //counter to keep track of already swapped elements ,, parallelising this area results in poor performance due to overhead ,,need to fix
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
        else                                                                                    //decending sort
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
void bitonicSequenceGenerator(int startIndex , int lastIndex , int *ar)                         //generate a bitonic sequence  from a a random order
{
    int noOfElements = lastIndex - startIndex +1;
      for(int j = 2;j<=noOfElements;j = j*2)
            {   
                #pragma omp parallel for                                                         //parallel implementation results in most performance gains here
                for(int i=0;i<noOfElements;i=i+j)
                {
                 if(((i/j)%2) ==0)                                                               //extra computation results in drastically lower performance ,need to fix
                 {
                     bitonicSortFromBitonicSequence(i,i+j-1,1,ar);
                 }   
                 else
                 {
                     bitonicSortFromBitonicSequence(i,i+j-1,0,ar);
                 }
                }
            }
}
int main()                                                                                        //main driver function
{   
    omp_set_dynamic(0);                                                                          //disabled so that the os doesnt override the thread settings
    cout<<"enter the number of threads ";                                                           
    int threads;
    cin>>threads;
    omp_set_num_threads(threads);                                                                //set the no of threads
    int n;
    cout<<"enter the number of elements to be sorted (number should be in the order of 2^n";     //try to fix this issue 
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
