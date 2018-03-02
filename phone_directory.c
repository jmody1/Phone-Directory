#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <math.h>


void create(char *inputfile);
void showDirectory();
void sortDirectory();
int size=0;
int flag1 = 0;

typedef struct
{
	char firstName[20];
	char lastName[20];
	char phoneNo[20];
} Contact;

Contact contact[1000];

typedef struct
{
	//char tempArray[20];
	char tempLeftFirst[20];
	char tempLeftLast[20];
	char tempRightFirst[20];
	char tempRightLast[20];	
	char tempLeftPhone[20];
	char tempRightPhone[20];
	char insertSameContact[20];
} Temp;

Temp temp[1000];

void mergeSort(Contact *A, int leftindex, int rightindex);
void merge(Contact *A, int leftindex, int midvalue, int rightindex);
int comparison(char *str1In, char *str2In);
int partition(Contact *A, int p, int q);
void randomQuick(Contact *A, int p, int rightindex);
int random1(int p, int rightindex);
void searchDirectory(char* name1, char* name2);
void deleteEntry(char* name);
void insertEntry(char* name, char* phone_number);


int main(int argc, char **argv) 
{
	char searchfirstname[20], searchlastname[20],firstname[20], lastname[20], phoneno[20];
	int switchinput;
	create(argv[1]);
	while(1)
	{
		printf("Please provide options:\n");
		printf("Insert			(press 1)\n");
		printf("Search			(press 2)\n");
		printf("Delete			(press 3)\n");
		printf("Show Directory		(press 4)\n");
		printf("Exit			(press 5)\n");

		scanf("%d",&switchinput);

		switch(switchinput)
		{
			case 1: printf("Enter Full name to insert: ");
				scanf("%s %s", &firstname, &lastname);
				
				printf("Enter phone number to insert: ");
				scanf("%s",&phoneno);

				strcat(firstname, ",");
				strcat(firstname, lastname);
	
				insertEntry(firstname, phoneno);
				break;
			
			case 2: printf("Enter full name to search in the directory: \n");
				scanf("%s %s",&searchfirstname, &searchlastname);
				searchDirectory(searchfirstname, searchlastname);
				break;

			case 3: printf("Enter Full name: ");
 				scanf("%s %s", &firstname, &lastname);
 				strcat(firstname, ",");
 				strcat(firstname, lastname);
				deleteEntry(firstname);
				break;
			
			case 4: showDirectory();
				break;
			
			case 5: exit(0);
				break;
		}
			getchar();

	}

}


void create(char *inputfile)
{
	FILE *file;
	char buffer[10000];

	file =fopen(inputfile,"r");
	if (!file)
	{
		printf("Invalid file. \n");;
	}

	char *split;

	while (fgets(buffer,10000, file)!=NULL)
	{
		split = strtok(buffer," ,");
		Contact *list = (Contact*) malloc (sizeof (Contact));
		strcpy(contact[size].firstName, split);
		split = strtok(NULL," ,");
		strcpy(contact[size].lastName, split);
		split = strtok(NULL," ,\n");
		strcpy(contact[size].phoneNo, split);
		size++;
	}
	fclose(file);
}


void showDirectory()
{
	sortDirectory();
	int i1=0;

	for(i1=0; i1<=size; i1++)
	{
   		printf(" %s %s %s \n",contact[i1].firstName, contact[i1].lastName, contact[i1].phoneNo);
	}
	
	
	
}


void sortDirectory()
{
//merge sort to sort names of person
//randomized quicksort to sort phone numbers if same first name and last name

	mergeSort(contact, 0, size - 1);
}


void mergeSort(Contact *A, int leftindex, int rightindex)
{
    if (leftindex < rightindex)
    {
        int midvalue = leftindex+(rightindex-leftindex)/2;
 
        // Sorting the left and right subarrays recursively
        mergeSort(A, leftindex, midvalue);
        mergeSort(A, midvalue+1, rightindex);
 
        merge(A, leftindex, midvalue, rightindex);
    }
}


void merge(Contact *A, int leftindex, int midvalue, int rightindex)
{
	int i,j,k;
	int n1 = midvalue - leftindex + 1;
	int n2 = rightindex - midvalue;

	//Temp tempLeftLast[size], tempRightLast[size],tempLeftFirst[size],tempRightFirst[size];
	//Temp tempLeftLast[n1], tempRightLast[n2],tempLeftFirst[n1],tempRightFirst[n2];

	//Store in members of temporary structures
	i=0, j=0;
	while(i<n1)
	{
		strcpy(temp[i].tempLeftLast, A[leftindex+i].lastName);
		strcpy(temp[i].tempLeftFirst, A[leftindex+i].firstName);
		strcpy(temp[i].tempLeftPhone, A[leftindex+i].phoneNo);
		i++;	
	}

	while(j<n2)
	{
	      strcpy(temp[j].tempRightLast, A[midvalue + 1+ j].lastName);	
	      strcpy(temp[j].tempRightFirst, A[midvalue + 1 + j].firstName);	
	      strcpy(temp[j].tempRightPhone, A[midvalue + 1 + j].phoneNo);
	      j++;	
	}

	//start index of left and right subarrays i.e i,j
	//start index after merging the left and right subarrays i.e k

	    for(i=0,j=0,k=leftindex ; i < n1 && j < n2;)
	    {
		if(comparison(temp[i].tempLeftLast, temp[j].tempRightLast)<0) 
	        {
	            strcpy(A[k].lastName, temp[i].tempLeftLast);
		    strcpy(A[k].firstName, temp[i].tempLeftFirst);
		    strcpy(A[k].phoneNo, temp[i].tempLeftPhone);
	            i++;
	        }
		else if(comparison(temp[i].tempLeftLast, temp[j].tempRightLast)==0)
		{
			if(comparison(temp[i].tempLeftFirst, temp[j].tempRightFirst)<0)
			{			
		    		strcpy(A[k].firstName, temp[i].tempLeftFirst);
				strcpy(A[k].lastName, temp[i].tempLeftLast);
				strcpy(A[k].phoneNo, temp[i].tempLeftPhone);
				i++;
			}
			else if(comparison(temp[i].tempLeftFirst, temp[j].tempRightFirst)==0)
			{
				//randomQuick(contact,0,size-1);
				//j++;
				if(comparison(temp[i].tempLeftPhone, temp[j].tempRightPhone)<=0)
				{
					strcpy(A[k].firstName, temp[i].tempLeftFirst);
					strcpy(A[k].lastName, temp[i].tempLeftLast);
					strcpy(A[k].phoneNo, temp[i].tempLeftPhone);
					i++;
				}
				else
				{
					strcpy(A[k].firstName, temp[j].tempRightFirst);
					strcpy(A[k].lastName, temp[j].tempRightLast);
					strcpy(A[k].phoneNo, temp[j].tempRightPhone);
					j++;
				}	
			}
			else
			{
				strcpy(A[k].firstName, temp[j].tempRightFirst);
				strcpy(A[k].lastName, temp[j].tempRightLast);
				strcpy(A[k].phoneNo, temp[j].tempRightPhone);
				j++;
			}	
		}
        	else
        	{
        	    strcpy(A[k].lastName, temp[j].tempRightLast);
		    strcpy(A[k].firstName, temp[j].tempRightFirst);
		    strcpy(A[k].phoneNo, temp[j].tempRightPhone);
        	    j++;
        	}
        k++;
    }
 
    //store the remaining elements of left subarray
    while (i < n1)
    {
        strcpy(A[k].lastName, temp[i].tempLeftLast);
	strcpy(A[k].firstName, temp[i].tempLeftFirst);
	strcpy(A[k].phoneNo, temp[i].tempLeftPhone);
        i++;
        k++;
    }
 
    //store the remaining elements of right subarray
    while (j < n2)
    {
        strcpy(A[k].lastName, temp[j].tempRightLast);
	strcpy(A[k].firstName, temp[j].tempRightFirst);
	strcpy(A[k].phoneNo, temp[j].tempRightPhone);
        j++;
        k++;
    }


}


int random1(int p, int r)
{
    return p + rand()%(r - p + 1); 
}


void randomQuick(Contact *A, int p, int r)
{
		/*int i = random(p,r);
	Contact temp = A[i];
			A[i] = A[r];
			A[r] = temp;*/

		if(p < r)
		{
			int q = partition(A,p,r);
			randomQuick(A,p,q-1);
			randomQuick(A,q+1,r);
		}
}



int partition(Contact *A, int p, int q)
{
	int pi = random1(p,q);
	Contact pivot = A[pi];

	Contact temp1 = A[pi];
	A[pi] = A[q];
	A[q] = temp1;

	int i = p-1;
	//int	pivot = q;
	int j=0;
	for(j=p; j<=q; j++)
	{
		if(comparison(A[j].lastName, pivot.lastName) == 0)
		//if(strcmp(A[j].lastName, pivot.lastName) == 0)
		{
			if(comparison(A[j].firstName, pivot.firstName) == 0)
			{
				if(comparison(A[j].phoneNo, pivot.phoneNo) < 0)
				{
					i++;
					Contact tempx = A[i];
					A[i] = A[j];
					A[j] = tempx;
				}
			}
		}
		
	}
	Contact tempx = A[i+1];
			A[i+1] = A[q];
			A[q] = tempx;
	return i+1;

}




int comparison(char *str1In, char *str2In)
{
	int result;
	char string1[15];
    	char string2[15];

   	strcpy(string1, str1In);
   	strcpy(string2, str2In);

	int length = sizeof(string2);
 	
	if(sizeof(string1) > sizeof(string2))
 	{
 		length = sizeof(string1);
 	}
 	int i=0;
	
	while(length>i)	
	{
 		string1[i] = tolower(string1[i]);
		string2[i] = tolower(string2[i]);
		i++;
	}
	result = strcmp(string1, string2);
	
	if(result < 0)
	{
	      return -1;
	}
	else if (result == 0)
	{
		return 0;
   	}
   	else
	{
		return 1;
   	}
   
}



void searchDirectory(char* name1, char* name2)
{
//search for name, if found, print the record, else print not found
	int i;
	int lowvalue;
	int highvalue = 0;	
	int midv;
	highvalue = size-1;
	//char insertSameContact[20];
		
	for(lowvalue = 0; lowvalue<=highvalue;)
	{
		midv = (lowvalue + highvalue)/2;
		if (strcmp(name2, contact[midv].lastName) == 0)
		{
			if(strcmp(name1, contact[midv].firstName) == 0)
			{
				printf("Name Found: \n");
				int x1,x2;				
				for(x1=midv+1;x1<=highvalue;x1++)
				{
					if(strcmp(contact[x1].firstName,name1)==0 & strcmp(contact[x1].lastName,name2)==0)
					{
						printf("%s %s %s\n", name1, name2, contact[x1].phoneNo);
					}
				}
				for(x2=midv;x2>=lowvalue;x2--)
				{
					if(strcmp(contact[x2].firstName,name1)==0 & strcmp(contact[x2].lastName,name2)==0)
					{
						printf("%s %s %s\n", name1, name2, contact[x2].phoneNo);
					}
				}
				flag1 = midv;
				strcpy(temp[0].insertSameContact, contact[midv].phoneNo);
				return 0;				
			}
			else if(strcmp(name1, contact[midv].firstName) > 0)
			{
				highvalue = highvalue;
				lowvalue = midv + 1;
			}
			else
			{
				lowvalue = lowvalue;
				highvalue = midv - 1;
			}
		}
		else if(strcmp(name2, contact[midv].lastName) > 0)
		{
			highvalue = highvalue;
			lowvalue = midv + 1;
		}
		else
		{
			lowvalue = lowvalue;
			highvalue = midv - 1;
		}
	}
	printf("name not found\n");
	flag1 = 0;	
}





void deleteEntry(char* name)
{
//delete entry, if multiple persons, delete last record in sorted order
//if not found, print cant delete

	char *first, *last;
	int c;
	first = strtok(name, ",");
	last = strtok(NULL, "");
	int z1,z2;
	for(z1 = size;z1>0;z1--)
	{
		if(strcmp(first,contact[z1].firstName)==0 & strcmp(last,contact[z1].lastName)==0)
		{
			printf("Contact Found\n");
			for(z2=z1;z2<=size;z2++)
			{
				contact[z2] = contact[z2+1];
			}
			printf("Record has been deleted from the directory!\n");
			return 0;
		}
	}
	printf("unable to delete as entry not found\n");
}


void insertEntry(char* name, char* phone_number)
{
//insert name and maintain sorted order, if name and phone number present, print already exists
	
	char *first, *last;
	first = strtok(name, ",");
	last = strtok(NULL, "");

	searchDirectory(first, last);
	if(flag1 != 0 & strcmp(temp[0].insertSameContact, phone_number)==0)
	{
		printf("entry already exist in the directory\n");
		return 0;
	}

	strcpy(contact[size].firstName, first);
	strcpy(contact[size].lastName, last);
	strcpy(contact[size].phoneNo, phone_number);
	size++;
	sortDirectory();
	printf("Added to the directory and sorted!\n");

}
