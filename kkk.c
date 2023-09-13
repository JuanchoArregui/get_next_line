#include <stdio.h>
#include <stdlib.h>
#include <string.h>


size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}





// Función 3: Recibe un puntero a la cadena estática y la modifica
void funcion3(char **cadena) {
    
    // Modifica la cadena estática
	if (*cadena != NULL)
   		free(*cadena);
	*cadena = malloc(4 * sizeof(char));
	(*cadena)[0] = 'A';
	(*cadena)[1] = 'B';
	(*cadena)[2] = 'C';
	(*cadena)[3] = '\0';
	printf("Función 3: Recibió = %p\n", cadena);
    printf("Función 3: pointer = %p\n", *cadena);
    printf("Función 3: cadena estática = %s\n", *cadena);

}

// Función 2: Recibe un puntero a la cadena estática y la modifica
void funcion2(char **cadena) {
    
    // Modifica la cadena estática
	if (*cadena != NULL)
		free(*cadena);
	*cadena = malloc(3 * sizeof(char));
	(*cadena)[0] = 'a';
	(*cadena)[1] = 'b';
	(*cadena)[2] = '\0';
    
    printf("Función 2: Recibió = %p\n", cadena);
    printf("Función 2: pointer = %p\n", *cadena);
    printf("Función 2: cadena estática = %s\n", *cadena);
    // Llama a la Función 3 y pasa el puntero a la cadena estática como argumento
    funcion3(cadena);
}

// Función 1: Define una cadena de caracteres estática
void funcion1(char **cadena) {
    

	*cadena = malloc(2 * sizeof(char));
	(*cadena)[0] = 'a';
	(*cadena)[1] = '\0';

    printf("Función 1: recibido = %p\n", cadena);
    printf("Función 1: pointer = %p\n", *cadena);
    printf("Función 1: Cadena estática = %s\n", *cadena);
    // Llama a la Función 2 y pasa el puntero a la cadena estática como argumento
    funcion2(cadena);
}

int main() {
	static char *cadenaEstatica;
    printf("\nmain: address cadenaEstatica = %p\n", &cadenaEstatica);
    printf("main: contenido cadenaEstatica = %p\n", cadenaEstatica);

    cadenaEstatica = malloc(1 * sizeof(char));
    printf("\nmain: address cadenaEstatica = %p\n", &cadenaEstatica);
    printf("main: contenido cadenaEstatica = %p\n", cadenaEstatica);
    free(cadenaEstatica);
    printf("\nmain: address cadenaEstatica = %p\n", &cadenaEstatica);
    printf("main: contenido cadenaEstatica = %p\n", cadenaEstatica);
     cadenaEstatica = malloc(1 * sizeof(char));
     printf("\nmain: address cadenaEstatica = %p\n", &cadenaEstatica);
    printf("main: contenido cadenaEstatica = %p\n", cadenaEstatica);
    free(*cadenaEstatica);
    printf("\nmain: address cadenaEstatica = %p\n", &cadenaEstatica);
    printf("main: contenido cadenaEstatica = %p\n", cadenaEstatica);

    char        *test;
    size_t      test_length;
    test = NULL;
    test_length = ft_strlen(test);
    printf("main: test_length = %lu\n", test_length);


    printf("main: address cadenaEstatica = %p\n", &cadenaEstatica);
    printf("main: contenido cadenaEstatica = %p\n", cadenaEstatica);


    // Llama a la Función 1
    funcion1(&cadenaEstatica);

    printf("main FINAL: pointer = %p\n", cadenaEstatica);
    printf("Cadena estática valor FINAL = %s\n", cadenaEstatica);

    free(cadenaEstatica);
    
    return 0;
}
