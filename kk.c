#include <stdio.h>

// Función 3: Recibe la variable estática como argumento y la multiplica
void funcion3(int *variable) {
    printf("Función 3: Recibió la variable estática = %d\n", *variable);
    
    // Multiplica la variable estática
    (*variable) *= 5;
    
    printf("Función 3: Multiplicó la variable estática = %d\n", *variable);
}

// Función 2: Recibe la variable estática como argumento y la incrementa
void funcion2(int *variable) {
    printf("Función 2: Recibió la variable estática = %d\n", *variable);
    
    // Incrementa la variable estática
   (*variable)++;
    
    printf("Función 2: Incrementó la variable estática = %d\n", *variable);
    
    // Llama a la Función 3 y pasa la variable estática como argumento
    funcion3(variable);
}

// Función 1: Define una variable estática y la inicializa a 0
void funcion1(int *variable) {
    
    printf("Función 1: Variable estática = %d\n", *variable);
    
    // Llama a la Función 2 y pasa la variable estática como argumento
    funcion2(variable);

}

int main() {
    static int variableEstatica = 0;
    // Llama a la Función 1
    funcion1(&variableEstatica);
	printf("\n");
    funcion1(&variableEstatica);
	printf("\n");
    funcion1(&variableEstatica);
    printf("\n\nVariable estática valor FINAL = %d\n", variableEstatica);

    
    return 0;
}
