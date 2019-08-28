#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct _CTempType {
	unsigned char c;
    int n;
	float f;
} CTempType;

void print( const CTempType* temp, int n )
{
	printf("%d : %x, %x, %f\n", n, temp->c, temp->n, temp->f);
}

int main(int argc, char *argv[])
{
	const char* strBinFileName = "temp.bin";

	CTempType cTemp1 = { 0x5a, 0x01020304, 1e01};
	CTempType cTemp2 = { 0x41, 0x0, 0. };

	print(&cTemp1, 1);
	print(&cTemp2, 2);

	int nBinFileDesc = open(strBinFileName, O_WRONLY | O_CREAT, 0700);
	int nBinWriteSize = write(nBinFileDesc, &cTemp1, sizeof(CTempType));
	close(nBinFileDesc);

	printf("%s, write size:%d\n" , strBinFileName, nBinWriteSize);

	nBinFileDesc = open(strBinFileName, O_RDONLY, 0700);
	int nBinReadSize = read(nBinFileDesc, &cTemp2, sizeof(CTempType));
	close(nBinFileDesc);

	print(&cTemp1, 1);
	print(&cTemp2, 2);

	printf("%s, read size:%d\n" , strBinFileName, nBinReadSize);

	return 0;
}
