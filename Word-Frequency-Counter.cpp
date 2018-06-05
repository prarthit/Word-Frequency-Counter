#include<iostream>
#include<string.h>
#include<fstream>
#include<vector>
#include<stdlib.h>
using namespace std;

int arrsize=0,svc=1,thres;

	int asci(string s)
	{
		int i,sum=0;
		for(i=0;i<s.size();i++)
		{
			sum=sum+s[i];
		}
		return sum;
	}
	
	string lowerCase(string isUpper)
{
    string toReplace = isUpper;
    for (int i = 0; i < toReplace.length(); i++) {
        if (toReplace[i] >= 65 && toReplace[i] <= 90) {
            toReplace[i] = tolower(toReplace[i]);
        }
    }
    return toReplace;
}


	struct node
	{
		int freq;
		string value;
		struct node *next;
	};
	
	struct hashk
	{
		struct node *head;
		int maxfreq;
		int numnodes;
	};
		
	struct node *createNode(string word1) 
	{
        struct node *newnode = new node;
        newnode->value=word1;
        newnode->freq = 1;
        newnode->next = NULL;
        return newnode;
    }
    
    struct node *tempNode=NULL;
    
    int search(int hashIndex,string value,struct hashk hashTable[])
{
	struct node *myNode;
	myNode = hashTable[hashIndex].head;
	int flag=0;
        while (myNode != NULL) 
		{
                if (myNode->value == value) 
				{
                    flag=1;
                    tempNode=myNode;
                    break;
                    
                }
				myNode = myNode->next;
        }
        
        if(flag!=1)
        {
        	return 0;	
		}
		else
		{
			return 1;
		}     

}
    
    
    void insertToHash(string word1,struct hashk hashTable[]) 
	{
        int hashIndex = (asci(word1))% svc;
        struct node *newnode = createNode(word1);
		if (hashTable[hashIndex].head==NULL)
		{
                hashTable[hashIndex].head = newnode;
                hashTable[hashIndex].numnodes = 1;
                hashTable[hashIndex].maxfreq = 1;
        }
         
        else if(search(hashIndex,word1,hashTable)==1)
        {
         	tempNode->freq++;
         	if(hashTable[hashIndex].maxfreq < tempNode->freq)
         	hashTable[hashIndex].maxfreq = tempNode->freq;
         	
		}
        
		else
		{
			newnode->next = (hashTable[hashIndex].head);
        	hashTable[hashIndex].head = newnode;
        	hashTable[hashIndex].numnodes++;
    	}
    }


	void insertArr(struct node *arr[],struct hashk hashTable[])
	{
		int i,k=0;
		struct node *myNode;
		myNode=NULL;
		
		for(i=0;i<svc;i++)
		{
			if(hashTable[i].maxfreq>thres)
			{
			
			myNode=hashTable[i].head;
			while(myNode!=NULL)
			{
				if((myNode->freq)>thres)
				{
					arr[k] = myNode;
					arr[k]->next=NULL;
					k++;
				}
				myNode=myNode->next;
		    }
		}
		}
		arrsize=k;
	}		

//struct node *arr2[svc];

void merge(struct node *arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    struct node *L[n1];
	struct node *R[n2];
 
    for (i = 0; i < n1; i++)
    {
	
        L[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++)
    {
	
        R[j] = arr[m + 1+ j];
    }
 
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if ((L[i]->freq) <= (R[j]->freq))
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
} 	

void mergeSort(struct node *arr[], int l, int r)
{
   if (l < r)
   {
      int m = l+(r-l)/2;
      mergeSort(arr, l, m);
      mergeSort(arr, m+1, r);
      merge(arr, l, m, r);
   }
   
}


int main()
{
	int i;
	ifstream text("text.txt");
	vector<string> svec;
	string word;
	cout<<"Enter threshold : "<<endl;
	cin>>thres;
	while(text>>word)
		{
			for (i = 0; i < word.length(); i++) 
			{
				if (!((word[i] >= 'a' && word[i]<='z') || (word[i] >= 'A' && word[i]<='Z') || word[i]=='\''))
        		{
            		word[i] = '\0';
       	 		}
			}
			
			word = lowerCase(word);
			svec.push_back(word);
			
		}
			
	svc=svec.size();
	
	struct hashk hashTable[svc];
	struct node *arr[svc];	
	
	for(i=0;i<svc;i++)
	{
		hashTable[i].head=NULL;
	}
				
	for(i=0;i<svc;i++)
	{
		insertToHash(svec[i],hashTable);
	}
	
	insertArr(arr,hashTable);

	mergeSort(arr, 0, arrsize-1);
	i=arrsize-1;
	while(i>=0)
	{
		cout<<arr[i]->value<<"--->"<<arr[i]->freq<<endl;
		i--;
	}

	return 1;

}



