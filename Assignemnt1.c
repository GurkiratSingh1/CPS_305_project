#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "QueueImplementation.c"

int rows,colums;
struct {
    int x;
    int y;
} directions[] = {{1,0,},{0,-1,},{-1,0},{0,1}};

char** array;
Queue checker;
ItemType temp;
FILE *fp;
ItemType test;
int count;
void printArray();
int isValid(int i, int j);
int findE(); 
void fixArray();
void createArray();
int main(int argc, char *argv[])
	{
	if(argc == 2)
	{
		fp = fopen(argv[1],"r");
		InitializeQueue(&checker);
		int i,j;
		int a[2],b[2];
	   	fscanf(fp," %i",a);
		fscanf(fp,"%i",b);
		rows = b[0];
		colums = a[0];
		array = malloc(rows * sizeof(char *));
		//test = malloc ((rows*colums)*sizeof(ItemType *));
		for(i = 0; i<rows; i++){
			array[i] = malloc(colums*sizeof(char*));
		}
		createArray();
		
		for(i =0; i <rows; i++)
		{
			for (j = 0; j<colums; j++)
			{
				if(array[i][j] == 's')
				{
					temp.x =i;
					temp.y = j;
					Insert(temp, &checker);
					if(findE()==0)
					{
						printf("Not Found\n");
						break;
					}
					else{
						array[i][j] = '*';
						printf("Found\n");
						//fixArray();
						break; 
					}
				}
			}
		}
		//fixArray();
		//printArray();
		createArray();	
	}
}
int findE()
{
	//ItemType test [rows*colums];
	count = 0;
	int k;
	while(Empty(&checker)==0)
	{
		Remove(&checker,&test);
		if(test.recorded != 1)
		{
			for(k = 0; k <4; k++)
			{
				if(isValid(test.x+directions[k].x,test.y+directions[k].y)!=0)
				{
					if(array[test.x+directions[k].x][test.y+directions[k].y] == '.')
					{
						array[test.x][test.y] = '*';
						temp.x =test.x+(directions[k].x);
						temp.y = test.y+(directions[k].y);
						//temp.value = '*';
						Insert(temp,&checker);
						array[test.x+directions[k].x][test.y+directions[k].y] = 'd';
					}
					else if(array[test.x+directions[k].x][test.y+directions[k].y] == 'e')
					{
						
						array[test.x][test.y] = '*';
						temp.x =test.x+(directions[k].x);
						temp.y = test.y+(directions[k].y);
						//stemp.value = '*';
						Insert(temp,&checker);
						array[test.x+directions[k].x][test.y+directions[k].y] = '*';
						return 1;
					}
				}
				
			}
					test.recorded = 1;
		}
		count++;
	}
	return 0;
}

int isValid(int i, int j)
	{
		// /int k;
		//printf("%i %ihell\n",i,j);
	if(i<rows && j<colums&&i >= 0&& j >=0){
		//if(count>0)
		/*for(k = 0; k<count-1; k++)
		{
			if(test[k].x == i && test[k].y ==j){	
				return 0;
			}
		}*/
		return 1;
	}
	
	
	return 0;
		
}
void createArray()
{
	int i,j;
	for(i =0; i <rows; i++)
	{
		for (j = 0; j<colums; j++)
		{
			fscanf(fp," %c", &array[i][j]);
			printf("%c", array[i][j]);
		}
		printf("\n");
	}
}
void printArray()
{
	int i,j;
	for(i =0; i <rows; i++)
	{
		for (j = 0; j<colums; j++)
		{
			if(array[i][j] == 'd')
				array[i][j] ='.';
		}
		//printf("\n");
	}
}
void fixArray()
{
	int i,k;//,j;
	for(i =count; i >0; i--)
	{
		for(k = 0; k <4; k++)
		{
			//printf("%i,%i,%i,%i\n",test[i-1].x,test[i].x+directions[k].x,test[i-1].y,test[i].y+directions[k].y);
			if((test[i-1].x== test[i].x+directions[k].x && test[i-1].y== test[i].y+directions[k].y)){
				array[test[i].x][test[i].y] ='*';
				//break; 
			//	i-=k;
			}
			
		}
	}
}
	