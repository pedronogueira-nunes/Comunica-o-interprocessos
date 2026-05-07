# Simulação Cliente-Servidor em C no Linux

## Descrição

Este projeto implementa uma simulação de comunicação entre processos utilizando o modelo cliente-servidor em linguagem C no sistema operacional Linux.

A aplicação demonstra como dois processos podem trocar informações através de sockets TCP/IP, onde:

- o servidor fica aguardando conexões;
- o cliente estabelece conexão;
- ocorre envio e recebimento de mensagens entre ambos.

O objetivo principal é demonstrar conceitos fundamentais de comunicação entre processos (IPC — Interprocess Communication) e redes de computadores.

---

# Funcionamento Geral

O sistema é dividido em dois programas:

## Servidor

O servidor:

1. cria um socket TCP;
2. associa o socket a uma porta;
3. entra em estado de espera;
4. aceita conexões de clientes;
5. recebe mensagens;
6. envia uma resposta ao cliente.

---

## Cliente

O cliente:

1. cria um socket TCP;
2. conecta ao servidor;
3. envia uma mensagem;
4. recebe a resposta do servidor;
5. encerra a conexão.

---

# Modelo de Comunicação

A comunicação foi implementada utilizando:

- protocolo TCP/IP;
- sockets do tipo SOCK_STREAM;
- comunicação orientada à conexão.

O endereço utilizado é:

```text
127.0.0.1