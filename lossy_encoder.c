#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

int low = 999;
int high = -999;
int t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17;

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
	unsigned char final_output2[256][128]; /* final image after quantization */

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
			
	fread(s,sizeof(unsigned char),image_size,fp);	// read the value of all pixels into the array
	
	k = 0;
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			img[i][j] = s[k];
			//img[i][j] = s[k] - 128;
			if ( img[i][j] > high)
				high = img[i][j];
			if ( img[i][j] < low)
				low = img[i][j];			
			//img[i][j] = s[k];
			k++;
		}
	}
	fclose(fp);
	
	printf("high = %d low = %d\n", high, low);
  int mydelta = (high - low)/16;
	
	t1 = low;
	t2 = low + mydelta;
	t3 = low + 2 * mydelta;
	t4 = low + 3 * mydelta;
	t5 = low + 4 * mydelta;
	t6 = low + 5 * mydelta;
	t7 = low + 6 * mydelta;
	t8 = low + 7 * mydelta;
	t9 = low + 8 * mydelta;
	t10 = low + 9 * mydelta;
	t11 = low + 10 * mydelta;
	t12 = low + 11 * mydelta;
	t13 = low + 12 * mydelta;
	t14 = low + 13 * mydelta;
	t15 = low + 14 * mydelta;	
	t16 = low + 15 * mydelta;	
	t17 = high;	

	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			if( img[i][j] >= t1 && img[i][j] < t2) {
				final_output[i][j] = 0;	
			}
			else if( img[i][j] >= t2 && img[i][j] < t3) {
				final_output[i][j] = 1;
			}
			else if( img[i][j] >= t3 && img[i][j] < t4) {
				final_output[i][j] = 2;		
			}
			else if( img[i][j] >= t4 && img[i][j] < t5) {
				final_output[i][j] = 3;
			}
			else if( img[i][j] >= t5 && img[i][j] < t6) {
				final_output[i][j] = 4;
			}
			else if( img[i][j] >= t6 && img[i][j] < t7) {
				final_output[i][j] = 5;
			}
			else if( img[i][j] >= t7 && img[i][j] < t8) {
				final_output[i][j] = 6;
			}
			else if( img[i][j] >= t8 && img[i][j] < t9) {
				final_output[i][j] = 7;
			}
			else if( img[i][j] >= t9 && img[i][j] < t10) {
				final_output[i][j] = 8;
			}	
			else if( img[i][j] >= t10 && img[i][j] < t11) {
				final_output[i][j] = 9;
			}
			else if( img[i][j] >= t11 && img[i][j] < t12) {
				final_output[i][j] = 10;
			}
			else if( img[i][j] >= t12 && img[i][j] < t13) {
				final_output[i][j] = 11;
			}
			else if( img[i][j] >= t13 && img[i][j] < t14) {
				final_output[i][j] = 12;
			}
			else if( img[i][j] >= t14 && img[i][j] < t15) {
				final_output[i][j] = 13;
			}									
			else if( img[i][j] >= t15 && img[i][j] < t16) {
				final_output[i][j] = 14;
			}				
			else {
				final_output[i][j] = 15;
			}
		}						
	}

	for(i=0;i<height;i++)
	{
		for(j=0;j<width/2;j++)
		{	
			final_output2[i][j] = ((final_output[i][j*2] << 4) | final_output[i][j*2+1]);
			//printf("final_output2 = %d\n", final_output2[i][j]);
		}	
	}
	
	fputs("P5\n",fp2);
	sprintf(temp,"%d\n",width);
	fputs(temp,fp2);
	sprintf(temp,"%d\n",height);
	fputs(temp,fp2);
	sprintf(temp,"%d\n",maxVal);
	fputs(temp,fp2);				
		
	fwrite(final_output2, sizeof(unsigned char), 32768, fp2 ); 
	//fwrite(final_output, 32, 65536, fp2 ); 
	return 0;
}