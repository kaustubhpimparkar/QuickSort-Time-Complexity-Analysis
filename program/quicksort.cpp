#include <iostream>
#include <cstdlib>
#include <ctime>
#include<string>

using namespace std;

long long int count1=0, count2 = 0;

void swap ( int* a, int* b ) // used for swapping in partition and select method 
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition (int arr[], int p, int r) // to place pivot as it's kth smallest place
{
    int pivot = arr[r];
    int i = (p - 1);
 
    for (int j = p; j <= r- 1; j++)
    {
    	if (arr[j] < pivot)
        {
            i++;
            swap (&arr[i], &arr[j]);
            count1++;
        }
        count2++;
    }
    swap (&arr[i + 1], &arr[r]);
    return (i + 1);
}

int select(int a[], int s, int e) // method to calculate median of medians
{
	if(e-s+1 <= 5){
		int temp,j;
		int k = (e-s)/2;
	
		for(int i=s+1;i<=e;i++){
		      temp=a[i];
		      j=i-1;
		      while((temp<a[j])&&(j>=0)){
		      a[j+1]=a[j];
		          j=j-1;
		      }
		      a[j+1]=temp;
		  }
	    
		return s+k;
	    }
	
	int m = (e-s+1)/5 + (e-s+1)%5;
	
	for(int i=0; i<m; i++){
	        int left = 5*i;
	        int right = left + 4;
	        if(right > e) right = e;
	        int median = select(a, left, right);
	        swap(&a[median], &a[i]);
	    }
	
	return select(a, 0, m);
}

int R_partition(int arr[], int p, int r) // method to get random index and switch it with last element
{	
	int pivot_index = (rand() % (r - p)) + p;
	swap(&arr[pivot_index], &arr[r]); //swap median of medias with last element for partitioning
	
	return partition(arr, p, r);
}

void QuickSort_median(int a[], int p, int r)
{
	if(p<r)
			{
			int med = select(a,p,r);
			swap(&a[med],&a[r]);
			int q = partition(a,p,r);
			QuickSort_median(a,p,q-1);                            
			QuickSort_median(a,q+1,r);
			}
}
void QuickSort_random(int a[], int p, int r)
{
	if(p<r)
			{
			int q = R_partition(a,p,r);                       
			QuickSort_random(a,p,q-1);                            
			QuickSort_random(a,q+1,r);
			}
}
void QuickSort_last(int a[], int p, int r)
{
	if(p<r)		
			{ 
			int q=partition(a,p,r);                       
			QuickSort_last(a,p,q-1);                             
			QuickSort_last(a,q+1,r);
			}
}

void display(int a[], int n, int start, std::string &version) // display time and comparisons for all versions
{
	// Print array after sorting
	
		/*cout<<"\nAfter Sorting : \n";
		for(int i=0;i<n;i++)
		{
		cout<<a[i]<<endl;
		}*/
		
		int stop = clock();
		
		cout<<version<<":\n";
		cout<<"total time in seconds: "<<(stop-start)/double(CLOCKS_PER_SEC)<<"\n";
		cout<<"total comparisons with pivot in partition method: "<<count1<<"\n";
		cout<<"total comparisons with swap with pivot only in partition method: "<<count2<<"\n\n";
}

int main() {
	
	int i,n,start;
	int *a = NULL;
	int ch=0;
	
	std::string version1 = "QS1(last element as pivot)";
	std::string version2 = "QS2(random number as pivot)";
	std::string version3 = "QS2(median of medians as pivot)";
	
	cout<<"\n------- QUICK SORT -------\n\n";
	
for(int k=0;k<=2;k++) // Four cases for number of elements in unsorted array, case 4 is excluded as it takes long time
{
	if(k==0)
		{
		n=100000;
		cout<<"Number of elements: 100000\n\n";
		}
	if(k==1)
		{
		n=1000000;
		cout<<"Number of elements: 1000000\n\n";
		}
	if(k==2)
		{
		n=10000000;
	    cout<<"Number of elements: 10000000\n\n";
		}
/*	if(k==3)
		{
		n=100000000;
		cout<<"Number of elements: 100000000\n\n";
		}*/
	
	a = new int[n]; //dynamic creation of array
	
	srand((unsigned)time(0)); // random generation of numbers input
	
	for(i=0;i<n;i++)
		a[i] = rand();
		
do  // loop for 3 quicksort versions
{
	ch++;
	switch(ch)
	{
	case 1:
	start = clock();
	
	QuickSort_last(a,0,n-1); 	
	display(a,n,start,version1);

	break;
	
	case 2:
	start = clock();
	
	QuickSort_random(a,0,n-1);
	display(a,n,start,version2);

	break;
	
	case 3: 
	/*start = clock();
	
	QuickSort_median(a,0,n-1);                        	  //Calling of QuickSort Function
	display(a,n,start,version3);*/
	;
	
	break;
	
	default: ;
	
	} 	
}while(ch!=4);
	
}//for loop end
	
	delete []a; // delete dynamic array
	a = NULL;
	
	return 0;
}