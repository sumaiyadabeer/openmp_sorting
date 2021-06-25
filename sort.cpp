#include <iostream>
#include <sstream>
#include "sort.h"
#include <omp.h> 
using namespace std;
//********************QUICK SORT*******************//
void pSort::swap(dataType *data1, dataType *data2)
{ 
     pSort::dataType *t = new pSort::dataType[1];
     *t = *data1; 
     *data1 = *data2; 
     *data2 = *t; 
} 

int pSort::partition (dataType *data, int low, int high) 
{ 
    int pivot,i;
    i = (low - 1); 
    pivot = (data+high)->key; 
 
    for (int j = low; j <= high-1; j++) 
    { 
        
        if ((data+j)->key <= pivot) 
        { 
            i++;    
            swap((data+i), (data+j)); 
        } 
    } 
    swap((data+i+1), (data+high)); 
    return (i + 1); 
} 

void pSort::quick_sort(dataType *data, int low, int high) 
{ 
    if (low < high) 
    {        
        int part = partition(data, low, high); 
        quick_sort(data, low, part - 1); 
        quick_sort(data, part + 1, high); 
    } 
} 
/*********************RADIX SORT***********************/
int pSort::getMaximum(dataType *data, int low, int high) 
{ 
    int mx = (data+low)->key; 
    for (int i = low; i < high; i++) 
        if ((data+i)->key > mx) 
            mx = (data+i)->key; 
    return mx; 
} 

void pSort::unit_sort(dataType *data, int low, int high, int exp) 
{ 
   
    pSort::dataType *output = new pSort::dataType[high-low];
    int i, count[10] = { 0 }; 
  
    
    for (i = low; i < high; i++) 
        count[((data+i)->key  / exp) % 10]++; 
    for (i = 1; i < 10; i++) 
        count[i] += count[i - 1]; 
  
    for (i = high-1; i >= low; i--) { 
        (output+(count[((data+i)->key / exp) % 10] - 1))->key = (data+i)->key; 

        *(output+(count[((data+i)->key / exp) % 10] - 1))->payload = *(data+i)->payload; 
        count[((data+i)->key / exp) % 10]--; 
    } 
  
    count[0]=0;
    for (i = low; i < high; i++) {
        (data+i)->key = (output+count[0])->key;
        *(data+i)->payload = *(output+count[0])->payload; 
        count[0]++;
    }
}

void pSort::radix_sort(dataType *data, int low, int high)
{
   int m = getMaximum(data, low,high); 
   int i;   
    for ( i = 1; m / i > 0; i *= 10) 
        unit_sort(data, low,high, i); 

} 

/**************************MERGE SORT*****************/
void pSort::merge(dataType *data, int low, int center, int high)
{
    int l1,l2,i,j,k;
    l1 = center - low+1;
    l2 = high  - center;

    pSort::dataType *LEFT = new pSort::dataType[l1];
    pSort::dataType *RIGHT = new pSort::dataType[l2];

    for(int i = 0; i < l1; i++)
        *(LEFT+i) = *(data+low + i);


    for(int j = 0; j < l2; j++)
        *(RIGHT+j) = *(data+center + j+1);

    i = 0;
    j = 0;
    k = low;

    while (i < l1 && j < l2)
    {
        if ((LEFT+i)->key <= (RIGHT+j)->key)
        {
            *(data+k)=*(LEFT+i);
            i++;
        }
        else
        {
            *(data+k)=*(RIGHT+j);
            j++;
        }
        k++;
    }
    while (i < l1)
    {
        *(data+k)=*(LEFT+i);
        i++;
        k++;
    }

    while (j < l2)
    {
        *(data+k)=*(RIGHT+j);
        j++;
        k++;
    }

}


void  pSort::merge_sort(dataType *data, int low, int high)
{
    if (low < high)
    {

        int m = (low + high - 1) / 2;


        merge_sort(data, low, m);
        merge_sort(data, m + 1, high);

        merge(data, low, m, high);
    }
}


/*************************BEST SORT*******************/
void pSort::heapify(dataType *data, int n, int i) 
{ 
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
  

    if (l < n && (data+l)->key > (data+largest)->key) 
        largest = l; 
  

    if (r < n && (data+r)->key > (data+largest)->key) 
        largest = r; 
  

    if (largest != i) { 
        swap(data+i, (data+largest)); 

        heapify(data, n, largest); 
    } 
} 

void pSort::heap_sort(dataType *data, int n) 
{ 
    int i;
    for ( i = n / 2 - 1;; i--){
        if(i < 0)
        break;
        heapify(data, n, i);
    } 
         
  
    
    for (int i = n - 1; i >= 0; i--) {        
        swap(data, data+i);        
        heapify(data, i, 0); 
    } 
}

void pSort::Rearrange(dataType *data, int ndata, int size, int index, int offset){
int length= ndata/size+2;
pSort::dataType *Temp = new pSort::dataType[length];
int k,j,i=0;
for (i=0;i<length;i++){
     *(Temp+i) = *(data + index+ i);  
 }

 i=0;
 while(offset){
     *(data+i)= *(Temp);
     i=i+1;
     offset=offset-1;
}
if(i!=0){
    k=1;
}else{
    k=0;
}

 while(i<ndata){
     j=0;
     for(j=0;j<size && i<ndata; j++){
         *(data+i)= *(Temp+k);
         i++;
     }
     k=k+1;   
 }

}

void pSort::init()
   {   
   //MPI_Init(NULL, NULL);
   }
void pSort::print(dataType *data, int low, int high)
{
      for (int i=low;i<high;i++)
      {
        cout<<(data+i)->key<<endl;
      }

}
void pSort::close()
   {
   //MPI_Finalize();
   }
void pSort::sort(dataType *data, int ndata, SortType sorter)
{
int n_record;

/*
   #pragma omp parallel //figure out how to execute only by parent
	{ 
        n_record=ndata/omp_get_num_threads();
    }

   #pragma omp parallel 
	{ 
        int lower,upper,rank;
        stringstream ss;
        
        
        rank=omp_get_thread_num();
        lower=n_record*rank;
        upper=lower+n_record; 
        if (omp_get_num_threads()==rank+1){
          upper=ndata;  
        } 
        ss<<"lower is: "<<lower<<" upper is: "<<upper<<" rank is: "<<rank<<endl;
        string str = ss.str();
        //cout<<str;

        //merge_sort(data,lower,upper-1); // now working fine
        //heap_sort(data+lower, upper-lower); //now working fine
        //quick_sort(data,lower,upper-1); //working
        //radix_sort(data,lower,upper); //working

        switch(sorter)
        {
        case BEST:
        //cout<<"BEST is selected"<<endl;
        heap_sort(data+lower, upper-lower); 
        break;
        case QUICK:
        //cout<<"QUIK is selected"<<endl;
        quick_sort(data,lower,upper-1);
        break;
        case MERGE:
        //cout<<"MERGE is selected"<<endl;
        merge_sort(data,lower,upper-1);
        break;
        case RADIX:
        //cout<<"RADIX is selected"<<endl;
        radix_sort(data,lower,upper);
        break;
        default:
        cout<<"no valid choice about type of sort function"<<endl;
        }

	} 

        int lower,upper;
        lower=0;
        upper=ndata;
        //print(data,lower,upper);

int num_thread;
   #pragma omp parallel //figure out how to execute only by parent
	{ 
        num_thread=omp_get_num_threads();
        //cout<<num_thread<<endl;
        n_record=ndata/omp_get_num_threads();
    }
while(1){
    if((num_thread)/2){
    omp_set_num_threads((num_thread+1)/2);
    n_record=n_record*2;

    
    }else{
        break;
    }

   #pragma omp parallel //do boundary upper and middle set
	{ 
        num_thread=omp_get_num_threads();
        
        int rank,upper,lower,middle;
        stringstream ss;

        rank=omp_get_thread_num();
        lower=rank*n_record;
        upper=rank*n_record+n_record-1;
        middle=(lower + upper + 1) / 2;//lower+(upper-lower)/2;
        
        if (rank+1==omp_get_num_threads()){
            // if last part has unbalanced middle part 
            if (upper-(n_record/2)<ndata-1){
                    upper=ndata-1;                    
                    middle=lower+(n_record/2);  
                    }
            // HANDLING OF last part of array with uneven distribution
                if (upper>ndata-1){//means it has not any pair
                    upper=ndata-1;                    
                    middle=lower;
                    
                    //chk if it is only process and set lower=0; upper=ndata-1 and middle=n record/2
                    if (omp_get_num_threads()==1){
                        lower=0;
                        upper=ndata-1;
                        middle=n_record/2;
                    }
                }
                if (upper!=ndata-1){ //deals with last segment being large
                    //middle=upper-n_record;
                    upper=ndata-1;
                    //change the middle
                    cout<<"changing middle and upper"<<endl;

                }
            //HANDLING LAST PART WITH NO PAIR
                    
        }
        ss<<num_thread<<" "<<rank<<" Calling merge with "<<lower<<" "<<middle<<" "<<upper<<endl;
        string str = ss.str();
        //cout<<str;
        merge(data, lower,middle-1 ,upper);

    }
}
   
 
      
        //cout<<"print after sorting"<<endl;
        //Rearrange(data,  ndata,  size,  index,  offset);
        

        //print(data,lower,upper);
        */
       int upper, lower;
       upper=ndata;
       lower=0;

       merge_sort(data,lower,upper-1);
       print(data,lower,upper);
      
   }



