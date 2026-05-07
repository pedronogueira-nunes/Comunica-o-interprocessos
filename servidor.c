#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include <arpa/inet.h>
#include <sys/socket.h>

#define PORTA 8080
#define TAM_BUFFER 1024

int main() {

    int servidor_fd;
    int cliente_fd;

    struct sockaddr_in servidor_endereco;
    struct sockaddr_in cliente_endereco;

    socklen_t cliente_tamanho;

    char buffer[TAM_BUFFER] = {0};

    // Cria socket TCP
    servidor_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (servidor_fd == -1) {
        printf("Erro ao criar socket.\n");
        exit(EXIT_FAILURE);
    }

    printf("Socket do servidor criado.\n");

    // Configura endereço do servidor
    servidor_endereco.sin_family = AF_INET;
    servidor_endereco.sin_addr.s_addr = INADDR_ANY;
    servidor_endereco.sin_port = htons(PORTA);

    // Associa socket à porta
    if (bind(
            servidor_fd,
            (struct sockaddr*)&servidor_endereco,
            sizeof(servidor_endereco)
        ) < 0) {

        printf("Erro no bind.\n");
        exit(EXIT_FAILURE);
    }

    printf("Bind realizado com sucesso.\n");

    // Coloca servidor em modo de espera
    if (listen(servidor_fd, 5) < 0) {
        printf("Erro no listen.\n");
        exit(EXIT_FAILURE);
    }

    printf("Servidor aguardando conexao...\n");

    cliente_tamanho = sizeof(cliente_endereco);

    // Aceita conexão do cliente
    cliente_fd = accept(
        servidor_fd,
        (struct sockaddr*)&cliente_endereco,
        &cliente_tamanho
    );

    if (cliente_fd < 0) {
        printf("Erro ao aceitar conexao.\n");
        exit(EXIT_FAILURE);
    }

    printf("Cliente conectado!\n");

    // Recebe mensagem do cliente
    recv(cliente_fd, buffer, TAM_BUFFER, 0);

    printf("Mensagem recebida do cliente:\n");
    printf("%s\n", buffer);

    // Resposta do servidor
    char resposta[] = "Mensagem recebida com sucesso!";

    send(cliente_fd, resposta, strlen(resposta), 0);

    printf("Resposta enviada ao cliente.\n");

    // Fecha sockets
    close(cliente_fd);
    close(servidor_fd);

    printf("Servidor encerrado.\n");

    return 0;
}