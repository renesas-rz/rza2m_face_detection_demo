
#include <stdio.h>
#include <stdlib.h>

static void print_cascade(void* cascade)
{
	int tdepth, ntrees, offset;
	int8_t* ptree;
	int8_t* tcodes;
	float* lut;
	float thr;
	int i, j, idx;
	
	tdepth = ((int*)cascade)[2];
	ntrees = ((int*)cascade)[3];
	
	offset = ((1<<tdepth)-1)*sizeof(int32_t) + (1<<tdepth)*sizeof(float) + 1*sizeof(float);
	ptree = (int8_t*)cascade + 2*sizeof(float) + 2*sizeof(int);
	
	printf("**********\r\n");
	printf("tdepth=%d, ntrees=%d\r\n",tdepth,ntrees);
	for(i=0; i<ntrees; ++i)
	{
		printf("**tree[%d]**\r\n",i);
		tcodes = ptree;
		lut = (float*)(ptree + ((1<<tdepth)-1)*sizeof(int32_t));
		thr = *(float*)(ptree + ((1<<tdepth)-1)*sizeof(int32_t) + (1<<tdepth)*sizeof(float));
		
		idx = 1;
		printf("*tcodes*\r\n");
		for(j=0; j<((1<<tdepth)-1); ++j){
			printf("%i %i %i %i",tcodes[4*j],tcodes[4*j+1],tcodes[4*j+2],tcodes[4*j+3]);
		}
		printf("\r\n*lut*\r\n");
		for(j=0; j<(1<<tdepth); ++j){
			printf("%4.2f ",lut[j]);
		}
		printf("\r\n thr=%f\r\n",thr);
		ptree = ptree + offset;
		
	}
}

int main(int argc, char* argv[])
{
	FILE* file = 0;
	void* cascade = 0;
	int size;
	
	if (argc == 2)
	{
		file = fopen(argv[1], "rb");
		
		if(!file)
		{
			printf("# cannot read cascade from '%s'\n", argv[1]);
			return 1;
		}
		
		fseek(file, 0L, SEEK_END);
		size = ftell(file);
		fseek(file, 0L, SEEK_SET);

		//
		cascade = malloc(size);
		printf ("Cascade Size=%d\r\n",size);

		if(!cascade || size!=fread(cascade, 1, size, file))
			return 1;

		print_cascade(cascade);
		
		//
		fclose(file);
		free(cascade);
	}
}