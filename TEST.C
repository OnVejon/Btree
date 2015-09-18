#include <time.h>
void Delay2s();
main()
{
	printf("HEllo!\n");
	Delay2s();
	printf("HEllo!\n");
	getch();
	
}
void Delay2s()
{
	clock_t start=clock();
	while((clock()-start)/CLK_TCK<2);
}