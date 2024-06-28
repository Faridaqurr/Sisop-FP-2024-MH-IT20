#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <crypt.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>
#include <time.h>
#include <stdbool.h>
#include <dirent.h>
#include <signal.h>

#define PORT 8080
#define BUF_SIZE 1024
#define MAX_USERS 100
#define SALT_LENGTH 16
//#define DISCORIT_DIR "/home/revalina/final_project/"
//#define USER_FILE "/home/revalina/final_project/users.csv"
//#define CHANNEL_FILE "/home/revalina/final_project/channels.csv"
#define USER_FILE "/home/farida/sisophush/DiscorIT/users.csv"
#define DISCORIT_DIR "/home/farida/sisophush/DiscorIT"
#define CHANNEL_FILE "/home/farida/sisophush/DiscorIT/channels.csv"

typedef struct {
    int socket;
    char username[BUF_SIZE];
    char cur_channel[BUF_SIZE];
    char cur_room[BUF_SIZE];
    char role[BUF_SIZE];
    int in_channel;
    int in_room;
    int is_logged_in;
    int is_monitor;
    int is_root;
    int user_id;
} Client;

Client clients[MAX_USERS] = {0};
int client_count = 0;

void *connection_handler(void *socket_desc);

void daemonize() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    if (setsid() < 0) {
        perror("setsid failed");
        exit(EXIT_FAILURE);
    }

    signal(SIGCHLD, SIG_IGN);

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    if (chdir("/") < 0) {
        perror("chdir failed");
        exit(EXIT_FAILURE);
    }

    open("/dev/null", O_RDWR); 
    dup(0);
    dup(0);
}

int main(int argc, char *argv[]) {

    //daemonize();

    int socket_desc, client_sock, c, *new_sock;
    struct sockaddr_in server, client;

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Could not create socket");
    }
    puts("Socket created");

    if(setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0) {
        perror("setsockopt(SO_REUSEADDR) failed");
        return 1;
    }
    
    if (setsockopt(socket_desc, SOL_SOCKET, SO_REUSEPORT, &(int){1}, sizeof(int)) < 0) {
        perror("setsockopt(SO_REUSEPORT) failed");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");

    listen(socket_desc, 3);

    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
    while ((client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c))) {
        puts("Connection accepted");

        pthread_t sniffer_thread;
        new_sock = malloc(1);
        *new_sock = client_sock;

        if (pthread_create(&sniffer_thread, NULL, connection_handler, (void*)new_sock) < 0) {
            perror("could not create thread");
            return 1;
        }

        puts("Handler assigned");
    }

    if (client_sock < 0) {
        perror("accept failed");
        return 1;
    }

    return 0;
}

void handle_register(char *username, char *password) {
    FILE *fp = fopen(USER_FILE, "r+");
    if (fp == NULL) {
        fp = fopen(USER_FILE, "w+");
        if (fp == NULL) {
            perror("Tidak dapat membuka atau membuat users.csv");
            return;
        }
    }

    char line[256];
    int id = 0;
    int is_first_user = 1;
    rewind(fp);

    while (fgets(line, sizeof(line), fp)) {
        id++;
        is_first_user = 0;
        char *token = strtok(line, ",");
        if (token && strcmp(token, username) == 0) {
            printf("Username sudah terdaftar\n");
            fclose(fp);
            return;
        }
    }

    char salt[SALT_LENGTH + 1];
    for (int i = 0; i < SALT_LENGTH; i++) {
        salt[i] = 'A' + (random() % 26); 
    }
    salt[SALT_LENGTH] = '\0';

    char *hashed_password = crypt(password, salt);
    if (hashed_password == NULL) {
        perror("crypt gagal");
        fclose(fp);
        return;
    }

    const char *role = is_first_user ? "ROOT" : "USER";

    fseek(fp, 0, SEEK_END);

    fprintf(fp, "%d,%s,%s,%s\n", id + 1, username, hashed_password, role);
    fclose(fp);
    
    printf("Registrasi berhasil. Pengguna '%s' terdaftar dengan peran: %s\n", username, role);
}

int handle_login(char *username, char *password, Client *client) {
    FILE *fp = fopen(USER_FILE, "r");
    if (fp == NULL) {
        perror("Unable to open users.csv");
        return 0;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        char stored_username[BUF_SIZE], stored_password[BUF_SIZE], stored_role[BUF_SIZE];
        int id;
        sscanf(line, "%d,%[^,],%[^,],%s", &id, stored_username, stored_password, stored_role);
        
        if (strcmp(stored_username, username) == 0) {
            char *hashed_input = crypt(password, stored_password);
            if (hashed_input == NULL) {
                perror("crypt failed");
                fclose(fp);
                return 0;
            }

            if (strcmp(hashed_input, stored_password) == 0) {
                strcpy(client->username, username);
                strcpy(client->role, stored_role);
                client->user_id = id;
                client->is_logged_in = 1;
                client->is_root = (strcmp(stored_role, "ROOT") == 0);
                fclose(fp);
                printf("Login successful for user: %s (Role: %s)\n", username, stored_role);
                return 1;
            } else {
                fclose(fp);
                printf("Incorrect password for user: %s\n", username);
                return 0;
            }
        }
    }

    fclose(fp);
    printf("User not found: %s\n", username);
    return 0;
}

int create_channel(char *channel_name, char *key, Client *client) {
    if (!client->is_logged_in) {
        return 0;
    }

    FILE *fp = fopen(CHANNEL_FILE, "a+");
    if (fp == NULL) {
        perror("Unable to open channels.csv");
        return 0;
    }

    int channel_id = 1;
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        channel_id++;
    }

    char salt[SALT_LENGTH + 1];
    for (int i = 0; i < SALT_LENGTH; i++) {
        salt[i] = 'A' + (random() % 26);
    }
    salt[SALT_LENGTH] = '\0';

    char *hashed_key = crypt(key, salt);
    if (hashed_key == NULL) {
        perror("crypt failed");
        fclose(fp);
        return 0;
    }

    fprintf(fp, "%d,%s,%s\n", channel_id, channel_name, hashed_key);
    fclose(fp);

    char channel_dir[256];
    snprintf(channel_dir, sizeof(channel_dir), "%s/%s", DISCORIT_DIR, channel_name);
    if (mkdir(channel_dir, 0777) != 0) {
        perror("Failed to create channel directory");
        return 0;
    }

    char admin_dir[256];
    snprintf(admin_dir, sizeof(admin_dir), "%s/admin", channel_dir);
    if (mkdir(admin_dir, 0777) != 0) {
        perror("Failed to create admin directory");
        return 0;
    }

    char auth_file[256];
    snprintf(auth_file, sizeof(auth_file), "%s/auth.csv", admin_dir);
    fp = fopen(auth_file, "w");
    if (fp == NULL) {
        perror("Unable to create auth.csv");
        return 0;
    }
    fprintf(fp, "%d,%s,%s\n", client->user_id, client->username, "ADMIN");
    fclose(fp);

    char log_file[256];
    snprintf(log_file, sizeof(log_file), "%s/user.log", admin_dir);
    fp = fopen(log_file, "w");
    if (fp == NULL) {
        perror("Unable to create user.log");
        return 0;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char datetime[20];
    strftime(datetime, sizeof(datetime), "%d/%m/%Y %H:%M:%S", t);

    fprintf(fp, "[%s] %s created channel %s\n", datetime, client->username, channel_name);
    fclose(fp);

    printf("Channel '%s' created successfully.\n", channel_name);
    return 1;
}

void list_users(int sock) {
    FILE *fp = fopen(USER_FILE, "r");
    if (fp == NULL) {
        perror("Unable to open users.csv");
        return;
    }

    char line[256];
    char users[BUF_SIZE] = "Users: ";
    while (fgets(line, sizeof(line), fp)) {
        char username[BUF_SIZE];
        sscanf(line, "%*d,%[^,],%*[^,],%*s", username);
        strcat(users, username);
        strcat(users, " ");
    }

    fclose(fp);
    send(sock, users, strlen(users), 0);
}

void edit_user(char *username, char *new_username, char *new_password, int sock) {
    FILE *fp = fopen(USER_FILE, "r+");
    if (fp == NULL) {
        perror("Unable to open users.csv");
        return;
    }

    char line[256];
    char new_lines[MAX_USERS][BUF_SIZE];
    int i = 0, user_found = 0;
    while (fgets(line, sizeof(line), fp)) {
        char stored_username[BUF_SIZE], stored_password[BUF_SIZE], stored_role[BUF_SIZE];
        int id;
        sscanf(line, "%d,%[^,],%[^,],%s", &id, stored_username, stored_password, stored_role);
        
        if (strcmp(stored_username, username) == 0) {
            user_found = 1;
            if (new_username) {
                strcpy(stored_username, new_username);
                send(sock, "Username updated successfully\n", 29, 0);
            }
            if (new_password) {
                char salt[SALT_LENGTH + 1];
                for (int j = 0; j < SALT_LENGTH; j++) {
                    salt[j] = 'A' + (random() % 26);
                }
                salt[SALT_LENGTH] = '\0';
                char *hashed_password = crypt(new_password, salt);
                if (hashed_password == NULL) {
                    perror("crypt failed");
                    fclose(fp);
                    return;
                }
                strcpy(stored_password, hashed_password);
                send(sock, "Password updated successfully\n", 29, 0);
            }
        }

        snprintf(new_lines[i++], sizeof(new_lines[i]), "%d,%s,%s,%s\n", id, stored_username, stored_password, stored_role);
    }

    if (!user_found) {
        send(sock, "User not found\n", 15, 0);
    } else {
        freopen(USER_FILE, "w", fp);
        for (int j = 0; j < i; j++) {
            fputs(new_lines[j], fp);
        }
    }

    fclose(fp);
}

void remove_user(char *username, int sock) {
    FILE *fp = fopen(USER_FILE, "r+");
    if (fp == NULL) {
        perror("Unable to open users.csv");
        return;
    }

    char line[256];
    char new_lines[MAX_USERS][BUF_SIZE];
    int i = 0, user_found = 0;
    while (fgets(line, sizeof(line), fp)) {
        char stored_username[BUF_SIZE];
        sscanf(line, "%*d,%[^,],%*[^,],%*s", stored_username);
        
        if (strcmp(stored_username, username) != 0) {
            strcpy(new_lines[i++], line);
        } else {
            user_found = 1;
        }
    }

    if (!user_found) {
        send(sock, "User not found\n", 15, 0);
    } else {
        freopen(USER_FILE, "w", fp);
        for (int j = 0; j < i; j++) {
            fputs(new_lines[j], fp);
        }
        send(sock, "User removed successfully\n", 26, 0);
    }

    fclose(fp);
}

void *connection_handler(void *socket_desc) {
    int sock = *(int*)socket_desc;
    char client_message[BUF_SIZE];
    int read_size;
    int client_index = -1;

    for (int i = 0; i < MAX_USERS; i++) {
        if (clients[i].socket == 0) {
            clients[i].socket = sock;
            client_index = i;
            client_count++;
            break;
        }
    }

    while ((read_size = read(sock, client_message, BUF_SIZE)) > 0) {
        client_message[read_size] = '\0';
        char username[BUF_SIZE], password[BUF_SIZE], command[BUF_SIZE];
        sscanf(client_message, "%s %s -p %s", command, username, password);

        if (strcmp(command, "REGISTER") == 0) {
            handle_register(username, password);
            send(sock, "Registration successful\n", 24, 0);
        } else if (strcmp(command, "LOGIN") == 0) {
            int login_result = handle_login(username, password, &clients[client_index]);
            if (login_result) {
                char success_msg[BUF_SIZE];
                snprintf(success_msg, sizeof(success_msg), "Login successful\n");
                send(sock, success_msg, strlen(success_msg), 0);
            } else {
                char fail_msg[] = "Login failed\n";
                send(sock, fail_msg, strlen(fail_msg), 0);
            }
        } else if (clients[client_index].is_logged_in) {
            char channel_name[BUF_SIZE], key[BUF_SIZE];

            if (sscanf(client_message, "CREATE CHANNEL %s -k %s", channel_name, key) == 2) {
                int result = create_channel(channel_name, key, &clients[client_index]);
                if (result) {
                    char success_msg[] = "Channel created successfully\n";
                    send(sock, success_msg, strlen(success_msg), 0);
                } else {
                    char fail_msg[] = "Failed to create channel\n";
                    send(sock, fail_msg, strlen(fail_msg), 0);
                }
            } else if (strcmp(command, "LIST") == 0 && strcmp(username, "USER") == 0) {
                list_users(sock);
            } else if (sscanf(client_message, "EDIT WHERE %s -u %s", username, password) == 2) {
                edit_user(username, password, NULL, sock);
            } else if (sscanf(client_message, "EDIT WHERE %s -p %s", username, password) == 2) {
                edit_user(username, NULL, password, sock);
            } else if (strcmp(command, "REMOVE") == 0) {
                remove_user(username, sock);
            } else {
                char fail_msg[] = "Invalid command\n";
                send(sock, fail_msg, strlen(fail_msg), 0);
            }
        } else {
            char fail_msg[] = "Invalid command\n";
            send(sock, fail_msg, strlen(fail_msg), 0);
        }
    }

    if (read_size == 0) {
        printf("Client disconnected\n");
        fflush(stdout);
    } else if (read_size == -1) {
        perror("recv failed");
    }

    clients[client_index].socket = 0;
    client_count--;
    free(socket_desc);
    return 0;
}
