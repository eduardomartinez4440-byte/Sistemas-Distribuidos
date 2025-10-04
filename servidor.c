#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>        // close()
#include <arpa/inet.h>     // socket(), bind(), listen(), accept()

int main() {
    int sockfd, cliente_sock;
    struct sockaddr_in servidor, cliente;
    socklen_t cliente_len = sizeof(cliente);
    int numero;

    // Crear socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("No se pudo crear el socket");
        exit(1);
    }

    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(5000);       // puerto
    servidor.sin_addr.s_addr = INADDR_ANY; // escuchar todas las interfaces

    // Bind
    if (bind(sockfd, (struct sockaddr *)&servidor, sizeof(servidor)) < 0) {
        perror("Error en bind");
        exit(1);
    }

    // Escuchar
    listen(sockfd, 5);
    printf("Servidor escuchando en puerto 5000...\n");

    // Aceptar conexión
    cliente_sock = accept(sockfd, (struct sockaddr *)&cliente, &cliente_len);
    if (cliente_sock < 0) {
        perror("Error en accept");
        exit(1);
    }

    printf("Cliente conectado: %s\n", inet_ntoa(cliente.sin_addr));

    while (1) {
        // Recibir número
        if (recv(cliente_sock, &numero, sizeof(int), 0) <= 0) {
            printf("Cliente desconectado\n");
            break;
        }

        // Convertir de network byte order a host byte order
        numero = ntohl(numero);

        printf("Cliente envió: %d\n", numero);

        if (numero == 0) {
            printf("Fin de la comunicación\n");
            break;
        }

        numero += 1; // incrementar

        // Convertir de host byte order a network byte order
        numero = htonl(numero);

        // Enviar respuesta
        send(cliente_sock, &numero, sizeof(int), 0);
    }

    close(cliente_sock);
    close(sockfd);
    return 0;
}
