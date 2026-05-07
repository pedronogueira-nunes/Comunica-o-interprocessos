#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include <arpa/inet.h>
#include <sys/socket.h>

#define PORTA 8080
#define TAM_BUFFER 1024

int main() {

    int cliente_fd;

    struct sockaddr_in servidor_endereco;

    char mensagem[TAM_BUFFER];
    char buffer[TAM_BUFFER] = {0};

    // Cria socket TCP
    cliente_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (cliente_fd == -1) {
        printf("Erro ao criar socket.\n");
        exit(EXIT_FAILURE);
    }

    printf("Socket do cliente criado.\n");

    // Configura endereço do servidor
    servidor_endereco.sin_family = AF_INET;
    servidor_endereco.sin_port = htons(PORTA);

    // Endereço localhost
    servidor_endereco.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Conecta ao servidor
    if (connect(
            cliente_fd,
            (struct sockaddr*)&servidor_endereco,
            sizeof(servidor_endereco)
        ) < 0) {

        printf("Erro ao conectar ao servidor.\n");
        exit(EXIT_FAILURE);
    }

    printf("Conectado ao servidor!\n");

    // Usuário digita mensagem
    printf("Digite uma mensagem para o servidor:\n");
    fgets(mensagem, TAM_BUFFER, stdin);

    // Envia mensagem
    send(cliente_fd, mensagem, strlen(mensagem), 0);

    printf("Mensagem enviada.\n");

    // Recebe resposta
    recv(cliente_fd, buffer, TAM_BUFFER, 0);

    printf("Resposta do servidor:\n");
    printf("%s\n", buffer);

    // Fecha socket
    close(cliente_fd);

    printf("Cliente encerrado.\n");

    return 0;
}