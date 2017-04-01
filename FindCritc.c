/*NAME OF PROGRAM:PERCOLATION 

DATE: 28TH JANUARY 2017

PROGRAMMER:ALDRIC ANTO ROSARIO.A

*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#define N 1000				//Number of sites in the 2D array

/*Function Declarations*/
void AddNewNeighbour(int ,int );
void NewSample(double );

/*********************************************************************/





double p,P_infi;			//Site occupation probability
bool occupied[N][N];	// NxN array to store the state of lattice.Bool is a data type used to store the result of conditional statements 


int clusters; 			//Number of clusters
int label[N][N];		//NxN array of cluster labels for each site
int currentLabel;		//Label of current cluster
int spanningLabel;		//Label of spanning cluster
int span;				//Number of spanning cluster
int size;
/*void initialize()		//this allocates memory to arrays
{
	

}*/

void AddNewNeighbour(int i,int j)
{
	if(occupied[i][j]&&label[i][j]==0)
	{
		label[i][j]=currentLabel;
		if(i<(N-1)) AddNewNeighbour(i+1,j);  //checking for clusters to the south
		
		if(i>0)  AddNewNeighbour(i-1,j);  //checking for clusters to the north
		
		if(j<(N-1))  AddNewNeighbour(i,j+1);  //checking for clusters to the east
		
		if(j>0)  AddNewNeighbour(i,j-1);  //checking for clusters to the west
	}

}


void NewSample(double p)
{	srand(time(NULL));
	//visit each site and occupy it with probability p
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			occupied[i][j]=(((float)rand())/RAND_MAX)<p ;  //returns a pseudo-random integer between 0 and RAND_MAX
			label[i][j]=0;  //not yet labeled
		}
	}
	//Find and label all clusters of occupied sites
	clusters=0;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			if(occupied[i][j]&&label[i][j]==0)
			{
				currentLabel=++clusters;  //Assigning new label
				AddNewNeighbour(i,j);  //adding new clusters
			}
		}
	}
	//Checking each cluster for percolation
	
	//spanningLabel=0;
	
	for(int cluster=1;cluster<=clusters;++cluster)
	{
		//check west boundary sites
		bool west=false;
		for(int j=0;j<N;j++)
		{
			if(label[j][0]==cluster){west=true;break;}
		}	
		
		//check east boundary sites
		bool east=false;
		for(int j=0;j<N;j++)
		{
			if(label[j][(N-1)]==cluster){east=true;break;}
		}	
		
		//check north boundary sites
		bool north=false;
		for(int j=0;j<N;j++)
		{
			if(label[0][j]==cluster){north=true;break;}
		}	
		
		//check south boundary sites
		bool south=false;
		for(int j=0;j<N;j++)
		{
			if(label[(N-1)][j]==cluster){south=true;break;}
		}
		
		if(west&&east&&south&&north)
		{
			spanningLabel=cluster;
			span++;
			
		}	
	}
	size=0;
	if(span != 0)
	{
		for(int j=0;j<N;j++)
			{
				for(int k=0;k<N;k++)
					{	
						if(label[j][k]==spanningLabel)size++;
			
					}
			}
	}
	P_infi=(size/N);	
	

}

void main()
{	

	clock_t begin = clock();
	/*int i;
	i=0;*/
	/*FILE *inp_prob;
	inp_prob=fopen("Size_of_spanning_cluster_different_probabilty","w");
	fprintf(inp_prob,"#This file contains the size of spanning cluster for different probability\n");
	fprintf(inp_prob,"#Probability \t Number of spanning clusters\n");*/
	
	FILE *inp_pinfi;
	inp_pinfi=fopen("PInfinity_vs_Probability_1000_9","w");
	fprintf(inp_pinfi,"#This file contains the P_infinity vs Probability \n");
	fprintf(inp_pinfi,"#Probability \t P_infinity\n");
	
	/*FILE *inp2_pinfi;
	inp2_pinfi=fopen("PInfinity_vs_Probability_1000_fine","w");
	fprintf(inp2_pinfi,"#This file contains the P_infinity vs Probability very fine between 0.58 and 0.6 in steps of 10^-6\n");
	fprintf(inp2_pinfi,"#Probability \t P_infinity\n");
	*/
	
	int i;
	float p_crit=0;
	/*float step_size1=0.001;*/
	float step_size2=0.000001;
	
	/*for(p=0.;p<0.4;(p=p+0.1))
	{			
		NewSample(p);
		fprintf(inp_pinfi,"%f\t%f\n",p,P_infi);
			
		if(p_crit == 0 && P_infi != 0)
		{
			p_crit=p;
			printf("\n The critical probability for size %d is %f\n",N,p_crit);
			
		}	
		
	}
	
	for(p=0.4;p<0.58;(p=p+step_size1))
	{			
		NewSample(p);
		fprintf(inp_pinfi,"%f\t%f\n",p,P_infi);
			
		if(p_crit == 0 && P_infi != 0)
		{
			p_crit=p;
			printf("\n The critical probability for size %d is %f\n",N,p_crit);
			
		}	
		
	}*/
	
	for(p=0.58;p<0.6;(p=p+step_size2))
	{			
		NewSample(p);
		fprintf(inp_pinfi,"%f\t%f\n",p,P_infi);
			
		if(p_crit == 0 && P_infi != 0)
		{
			p_crit=p;
			printf("\n The critical probability for size %d is %f\n",N,p_crit);
			
		}	
		
	}
	
	/*for(p=0.6;p<0.65;(p=p+step_size1))
	{			
		NewSample(p);
		fprintf(inp_pinfi,"%f\t%f\n",p,P_infi);
			
		if(p_crit == 0 && P_infi != 0)
		{
			p_crit=p;
			printf("\n The critical probability for size %d is %f\n",N,p_crit);
			
		}	
		
	}*/
	
	
	
	
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("\n The time spent running this program is %f\n",time_spent);
	
	
}


