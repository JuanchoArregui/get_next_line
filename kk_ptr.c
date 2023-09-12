# include <stdio.h>
# include <stdlib.h>

int	main(void)
{
	char *ptrToChar;
	ptrToChar = NULL;
	printf("\nantes de malloc");

	printf("\ndirección de ptrToChar: %p", &ptrToChar);
	printf("\ncontenido de ptrToChar: %p", ptrToChar);
	printf("\n");

	ptrToChar = malloc(5 * sizeof(char));
	if (!ptrToChar)
		return (1);
	ptrToChar[0] = 'h';
	ptrToChar[1] = 'o';
	ptrToChar[2] = 'l';
	ptrToChar[3] = 'a';
	ptrToChar[4] = '\0';
	printf("\nDESPUES DE MALLOC");

	printf("\ndirección de ptrToChar: %p", &ptrToChar);
	printf("\ncontenido de ptrToChar: %p", ptrToChar);
	printf("\nINDIRECCION char de ptrToChar: %c", *ptrToChar);
	printf("\nINDIRECCION string de ptrToChar: %s", ptrToChar);

	printf("\n");
	free(ptrToChar);

	return (0);
}