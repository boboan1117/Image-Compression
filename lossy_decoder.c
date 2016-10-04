#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

int main(int argc, char **argv)
{

	FILE *fp,*fp2;
	char infile[80], outfile[80];
	char temp[10];
	int i,j,k,b;
	int c;
	char ch;
	int type;
	int width, height, maxVal;
	int image_size;
	unsigned char s[65536];		/* array to read in binary file */
	char img[256][256];				/* array to store scaled image */
	unsigned char final_output[256][256]; /* final image after quantization */
	int block_num;
	
	while((c=getopt(argc,argv,"i:o:c:s:h"))!=EOF)
	{
		switch(c){
			/* input file */
			case 'i':
				strcpy(infile,optarg);
				if((fp=fopen(infile,"rb"))==NULL){
                fprintf(stderr,"Image file cannot be opened for input.\n");
                return;
				}
				break;

			/* output file */
			case 'o':
				strcpy(outfile,optarg);
				if((fp2=fopen(outfile,"wb"))==NULL){
                fprintf(stderr,"Output file cannot be opened for output.\n");
                return;
				}
				break;
		}
	}

	ch = getc(fp);		//get the 1st charactor
	if(ch != 'P')
	{
		printf("ERROR(1): Not valid pgm/ppm file type\n");
		exit(1);
	}
	
	ch = getc(fp);	// get the 2nd charactor
	type = ch - 48;	// convert it to integer
	if(type != 5)
	{
	   printf("ERROR(2): Not valid pgm file type\n");
	   exit(1);
	}
	
	while(getc(fp) != '\n');             // skip to end of line
	while (getc(fp) == '#')              // skip comment lines 
	{
	  while (getc(fp) != '\n');          // skip to end of comment line
	}
	
	fseek(fp, -1, SEEK_CUR);			// backup one character
	
	
	fscanf(fp,"%d", &width);	//read the image width
	fscanf(fp,"%d", &height); //read the image height
	fscanf(fp,"%d", &maxVal); //read the image max value
	image_size = width * height;	//calculate the total pixels
	
	printf("width  = %d\n",width);
	printf("height = %d\n",height);
	printf("maxVal = %d\n",maxVal);	
	printf("image_size = %d\n",image_size);	
			
	fread(s,sizeof(unsigned char),image_size/2,fp);	// read the value of all pixels into the array
	//fread(s,8,image_size,fp);	// read the value of all pixels into the array

	
	k = 0;
	for(i=0;i<height;i++)
	{
		for(j=0;j<width/2;j++)
		{
			img[i][j] = s[k];
			k++;
		}
	}
	fclose(fp);	
	
	//initialize();

	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			int tmp;
			//printf("img[i][j] == %d\n",img[i][j]);
			if( j%2 == 0)
				tmp = (img[i][j/2] & 0xf0) >> 4;
			else
				tmp = img[i][j/2] & 0xf;
				
			//printf("tmp == %d\n",tmp);
			
			if( tmp == 0) {
				final_output[i][j] = 8;	
			}
			else if( tmp == 1) {
				final_output[i][j] = 24;	
			}
			else if( tmp == 2) {
				final_output[i][j] = 40;
			}
			else if( tmp == 3) {
				final_output[i][j] = 56;		
			}
			else if( tmp == 4) {
				final_output[i][j] = 72;
			}
			else if( tmp == 5) {
				final_output[i][j] = 88;
			}
			else if( tmp == 6) {
				final_output[i][j] = 104;
			}
			else if( tmp == 7) {
				final_output[i][j] = 120;
			}
			else if( tmp == 8) {
				final_output[i][j] = 136;
			}
			else if( tmp == 9) {
				final_output[i][j] = 152;		
			}
			else if( tmp == 10) {
				final_output[i][j] = 168;
			}
			else if( tmp == 11) {
				final_output[i][j] = 184;
			}
			else if( tmp == 12) {
				final_output[i][j] = 200;
			}
			else if( tmp == 13) {
				final_output[i][j] = 216;
			}			
			else if( tmp == 14) {
				final_output[i][j] = 232;
			}		
			else {
				final_output[i][j] = 248;
			}
		}						
	}
	
	fputs("P5\n",fp2);
	sprintf(temp,"%d\n",width);
	fputs(temp,fp2);
	sprintf(temp,"%d\n",height);
	fputs(temp,fp2);
	sprintf(temp,"%d\n",maxVal);
	fputs(temp,fp2);				
		
	fwrite(final_output, sizeof(char), 65536, fp2 ); 
	//fwrite(final_output, sizeof(unsigned char), 65536, fp2 ); 
	return 0;
}	

