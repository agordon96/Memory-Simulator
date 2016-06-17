#include <stdio.h>
#include <stdlib.h>

#define MEM 128

typedef struct Process{
	char name;
	int numSwapped;
	int value;
}Process;

int main(int argc, char *argv[]){
	FILE *file;
	Process proc[26]; //processes for every letter of the alphabet
	Process queue[26]; //dynamic queue for processes
	Process memArray[MEM]; //allocated memory array
	char swapPriority[MEM]; //tells you which memory blocks have been in longest by letter
	int holes = 1; //num of total holes, is used for the memArray
	int i, j, k, x;
	int isTooBig, worstI, bestI;
	double loads, totalMemUsage, totalProcUsage, totalHoles, currentMemUsage; //used for averages
	int memProc = 0; //num of processes in memory
	int numProc = 0; //num of processes in file
	int queueLength = 0;
	int temp;
	
	i = 0;
	memArray[0].name = '@';
	memArray[0].value = MEM;

	if(argc != 2)
		printf("The format is ./holes <filename>.\n");
	
	file = fopen(argv[1], "r");
	if(file == 0){
		printf("File failed to open.\n");
		exit(0);
	}
	
	while(fscanf(file, "%c %d\n", &proc[i].name, &proc[i].value) != EOF){
		if(proc[i].value > MEM){
			proc[i].numSwapped = 3;
		}else{
			proc[i].numSwapped = 0;
			queue[queueLength] = proc[i];
			queueLength++;
		}
		i++;
		numProc++;
	}
	for(k = 0; k < 4; k++){
		loads = 0;
		totalMemUsage = 0;
		totalProcUsage = 0;
		totalHoles = 0;
		memProc = 0;
		holes = 1;
		
		/*if(k == 2){
			printf("Next fit currently inoperational. Switching to worst fit...\n");
			k = 3;
		}*/
	
		if(k == 0)
			printf("\n\nCommencing first fit allocation strategy...\n\n");
		else if(k == 1)
			printf("\n\nCommencing best fit allocation strategy...\n\n");
		else if(k == 2)
			printf("\n\nCommencing next fit allocation strategy...\n\n");
		else
			printf("\n\nCommencing worst fit allocation strategy...\n\n");
			
		while(queueLength > 0){ 
			isTooBig = 1;
			temp = holes + memProc;
			worstI = 0;
			bestI = 99999;
			for(i = 0; i < temp; i++){
				if(memArray[i].name == '@' && memArray[i].value >= queue[0].value){
					isTooBig = 0;
					if(memArray[i].value > worstI)
						worstI = i;
					if(memArray[i].value < bestI)
						bestI = i;
				}
				//printf("%c %d\n", memArray[i].name, memArray[i].value);
			}
		
			for(i = 0; i < temp; i++){
				if((memArray[i].name == '@' && memArray[i].value >= queue[0].value 
					&& (k == 0 || k == 2)) || (k == 1 && isTooBig == 0) 
					|| (k == 3 && isTooBig == 0)){
					if(k == 1)
						i = bestI;
					if(k == 3)
						i = worstI;
	
					if(memArray[i].value > queue[0].value){
						for(j = (holes + numProc); j > i; j--) //shift the memArray to the right if the process doesn't fill the hole
							memArray[j] = memArray[j - 1];
						memArray[i + 1].value -= queue[0].value;
					}else{
						holes--;
					}
					memArray[i] = queue[0];
					swapPriority[memProc] = memArray[i].name;
					memProc++;
					isTooBig = 0;
					loads++;
					x = 0;
					for(j = 0; j < (memProc + holes); j++){
						if(memArray[j].name != '@')
							x += memArray[j].value;
					}
					currentMemUsage = (x * 100) / MEM;
					totalMemUsage += currentMemUsage;
					totalProcUsage += memProc;
					totalHoles += holes;
					
					printf("pid loaded, #processes = %d, #holes = %d, %%memusage = %.0f, cumulative %%mem = %.0f\n"
						, memProc, holes, currentMemUsage, totalMemUsage / loads);
					
					for(j = 0; j < (queueLength - 1); j++) //shift the queue to the left
						queue[j] = queue[j + 1];
					queueLength--;
					
					if(k != 2){
						printf("asd\n");
						break;
					}
				}
			}
		
			if(isTooBig){
				temp = memProc + holes;
				for(i = 0; i < temp; i++){
					if(swapPriority[0] == memArray[i].name){
						for(j = 0; j < (memProc - 1); j++)
							swapPriority[j] = swapPriority[j + 1];
					
						memArray[i].numSwapped++;
						if(memArray[i].numSwapped < 3){
							queue[queueLength] = memArray[i];
							queueLength++;
						}
					
						x = 0;
						if(i > 0 && (i + 1) != (memProc + holes)){
							if('@' == memArray[i + 1].name && '@' == memArray[i - 1].name){
								memArray[i - 1].value += (memArray[i].value + memArray[i + 1].value);
								holes--;
								x = 1;
							}else if('@' == memArray[i + 1].name){
								memArray[i].value += memArray[i + 1].value;
								memArray[i].name = '@';
								x = 2;
							}else if('@' == memArray[i - 1].name){
								memArray[i - 1].value += memArray[i].value;
								x = 3;
							}else{
								memArray[i].name = '@';
								holes++;
							}
						}else if((i + 1) != (memProc + holes)){
							if('@' == memArray[i + 1].name){
								memArray[i].value += memArray[i + 1].value;
								memArray[i].name = '@';
								x = 2;
							}else{
								memArray[i].name = '@';
								holes++;
							}
						}else if(i > 0){
							if('@' == memArray[i - 1].name){
								memArray[i - 1].value += memArray[i].value;
								x = 3;
							}else{
								memArray[i].name = '@';
								holes++;
							}
						}else{
							memArray[i].name = '@';
							holes++;
						}
						memProc--;
					
						if(x == 1){
							for(j = i; j < (memProc + holes); j++){
								memArray[j] = memArray[j + 2];
							}
						}else if(x == 2){
							for(j = (i + 1); j < (memProc + holes); j++){
								memArray[j] = memArray[j + 1];
							}
						}else if(x == 3){
							for(j = i; j < (memProc + holes); j++){
								memArray[j] = memArray[j + 1];
							}
						}
					
						break;
					}
				}
			}
		}
		printf("Total loads = %.0f, average #processes = %.1f, average #holes = %.1f, cumulative %%mem = %.0f\n"
			, loads, totalProcUsage / loads, totalHoles / loads, totalMemUsage / loads);
	
		memArray[0].value = MEM;
		memArray[0].name = '@';
		for(i = 0; i < numProc; i++){//reset the queue
			if(proc[i].value <= MEM){
				proc[i].numSwapped = 0;
				queue[queueLength] = proc[i];
				queueLength++;
			}
		}
	}

	return 0;
}
