#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>        // close()
#include <arpa/inet.h>     // socket(), connect(), sockaddr_in

int main() {
    int sock;
    struct sockaddr_in servidor;
    char mensaje[1024], buffer[1024];

    // Crear socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("No se pudo crear el socket");
        return 1;
    }

    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(5000); // puerto del servidor
    servidor.sin_addr.s_addr = inet_addr("127.0.0.1"); // IP del servidor

    // Conectar al servidor
    if (connect(sock, (struct sockaddr *)&servidor, sizeof(servidor)) < 0) {
        perror("Error en la conexión");
        return 1;
    }

    printf("Conectado al servidor\n");

    // Enviar mensaje
    strcpy(mensaje, "Hola");
    if (send(sock, mensaje, strlen(mensaje), 0) < 0) {
        perror("Error al enviar");
        return 1;
    }

    // Recibir respuesta
    int bytes = recv(sock, buffer, sizeof(buffer) - 1, 0);
    if (bytes < 0) {
        perror("Error al recibir");
        return 1;
    }
    buffer[bytes] = '\0';
    printf("Servidor responde: %s\n", buffer);

    close(sock);
    return 0;
}
