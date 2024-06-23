#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <crypt.h>
#include <errno.h>

#define PORT 8080

void handle_response(int socket);

int main(int argc, char const *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <COMMAND> <ARGS>\n", argv[0]);
        return 1;
    }

    const char *command = argv[1];
    int sock = 0;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    char message[1024] = {0};

    if (strcmp(command, "REGISTER") == 0) {
        if (argc < 5) {
            fprintf(stderr, "Usage: %s REGISTER <USERNAME> -p <PASSWORD>\n", argv[0]);
            return 1;
        }
        const char *username = argv[2];
        const char *password_flag = argv[3];
        const char *password = argv[4];

        if (strcmp(password_flag, "-p") != 0) {
            fprintf(stderr, "Invalid usage. Use -p for password.\n");
            return 1;
        }

        char *hashed_password = crypt(password, "$6$abcdefghijk$");
        snprintf(message, sizeof(message), "%s %s %s", command, username, hashed_password);

    } else if (strcmp(command, "LOGIN") == 0) {
        if (argc < 5) {
            fprintf(stderr, "Usage: %s LOGIN <USERNAME> -p <PASSWORD>\n", argv[0]);
            return 1;
        }
        const char *username = argv[2];
        const char *password_flag = argv[3];
        const char *password = argv[4];

        if (strcmp(password_flag, "-p") != 0) {
            fprintf(stderr, "Invalid usage. Use -p for password.\n");
            return 1;
        }

        char *hashed_password = crypt(password, "$6$abcdefghijk$");
        snprintf(message, sizeof(message), "%s %s %s", command, username, hashed_password);

    } else if (strcmp(command, "LIST") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Usage: %s LIST <CHANNEL|ROOM|USER> [CHANNEL_NAME]\n", argv[0]);
            return 1;
        }
        const char *subcommand = argv[2];
        if (strcmp(subcommand, "CHANNEL") == 0) {
            snprintf(message, sizeof(message), "%s CHANNEL", command);
        } else if (strcmp(subcommand, "ROOM") == 0 && argc == 4) {
            const char *channel_name = argv[3];
            snprintf(message, sizeof(message), "%s ROOM %s", command, channel_name);
        } else if (strcmp(subcommand, "USER") == 0 && argc == 4) {
            const char *channel_name = argv[3];
            snprintf(message, sizeof(message), "%s USER %s", command, channel_name);
        } else {
            fprintf(stderr, "Invalid LIST command usage\n");
            return 1;
        }

    } else if (strcmp(command, "JOIN") == 0) {
        if (argc < 4) {
            fprintf(stderr, "Usage: %s JOIN <CHANNEL|ROOM> <NAME>\n", argv[0]);
            return 1;
        }
        const char *subcommand = argv[2];
        const char *name = argv[3];
        snprintf(message, sizeof(message), "%s %s %s", command, subcommand, name);

    } else {
        fprintf(stderr, "Unknown command\n");
        return 1;
    }

    send(sock, message, strlen(message), 0);
    handle_response(sock);

    close(sock);
    return 0;
}

void handle_response(int socket) {
    char buffer[1024] = {0};
    int valread = read(socket, buffer, 1024);
    buffer[valread] = '\0';
    printf("%s", buffer);
}
