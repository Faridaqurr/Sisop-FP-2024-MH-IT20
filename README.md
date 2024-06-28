# FINAL PROJECT SISTEM OPERASI
## Kelompok IT20
### Anggota Kelompok :
|             Nama              |     NRP    |
|-------------------------------|------------|
| Revalina Fairuzy Azhari Putri | 5027231001 |
| Farida Qurrotu 'Ayuna         | 5027231015 |
| Gallant Damas Hayuaji         | 5027231037 |

## SOAL

**A. Autentikasi**
  - Setiap user harus memiliki username dan password untuk mengakses DiscorIT. Username, password, dan global role disimpan dalam file user.csv.
  
  - Jika tidak ada user lain dalam sistem, user pertama yang mendaftar otomatis mendapatkan role "ROOT". Username harus bersifat unique dan password wajib di encrypt menggunakan menggunakan bcrypt.

![image](https://github.com/Faridaqurr/Sisop-FP-2024-MH-IT20/assets/150933246/f37c25cf-72bb-4ec1-bad1-75c9ccd98076)

![image](https://github.com/Faridaqurr/Sisop-FP-2024-MH-IT20/assets/150933246/26630e2c-8033-4b3e-bd50-dfa356ae932e)

**B. Bagaimana DiscorIT digunakan**

  **Perbedaan Akses antara Root, Admin, dan User :**
  - Root: Memiliki akses penuh untuk mengelola semua channel, room, dan user. Root adalah akun yang pertama kali mendaftar.
    
  - Admin: Memiliki akses untuk mengelola channel dan room yang mereka buat, serta mengelola user dalam channel mereka.
  
  - User: Dapat mengirim pesan chat, melihat channel, dan room. user menjadi admin di channel yang mereka buat.

![image](https://github.com/Faridaqurr/Sisop-FP-2024-MH-IT20/assets/150933246/ffb7f140-3471-42c7-8806-fc6f0e748f68)

![image](https://github.com/Faridaqurr/Sisop-FP-2024-MH-IT20/assets/150933246/acef0958-c079-43f6-b980-12bfac2eed9a)

User dapat masuk ke room setelah bergabung dengan channel.

![image](https://github.com/Faridaqurr/Sisop-FP-2024-MH-IT20/assets/150933246/439e2a31-53e9-4060-88f7-f98c07b69dee)

![image](https://github.com/Faridaqurr/Sisop-FP-2024-MH-IT20/assets/150933246/191b8d25-b8a0-48f8-b547-7cd586d8349a)

**C. Root**
  - Akun yang pertama kali mendaftar otomatis mendapatkan peran "root".
  
  - Root dapat masuk ke channel manapun tanpa key dan create, update, dan delete pada channel dan room, mirip dengan admin [D].
  
  - Root memiliki kemampuan khusus untuk mengelola user, seperti: list, edit, dan Remove.

![image](https://github.com/Faridaqurr/Sisop-FP-2024-MH-IT20/assets/150933246/4ffdc5db-bee2-4bec-8310-601389b8930b)

**D. Admin Channel**
  - Setiap user yang membuat channel otomatis menjadi admin di channel tersebut. Informasi tentang user disimpan dalam file auth.csv.
  
  - Admin dapat create, update, dan delete pada channel dan room, serta dapat remove, ban, dan unban user di channel mereka.

![image](https://github.com/Faridaqurr/Sisop-FP-2024-MH-IT20/assets/150933246/106df332-a236-4636-bd17-d8ada5334957)

![image](https://github.com/Faridaqurr/Sisop-FP-2024-MH-IT20/assets/150933246/5356cfb3-2d49-41e9-9d94-b5dd381c83b5)

![image](https://github.com/Faridaqurr/Sisop-FP-2024-MH-IT20/assets/150933246/f90414fa-5a02-4a42-8cbb-a20f12d1f37a)

![image](https://github.com/Faridaqurr/Sisop-FP-2024-MH-IT20/assets/150933246/7d8ccc8a-4685-458c-8829-4efed04724a7)

![image](https://github.com/Faridaqurr/Sisop-FP-2024-MH-IT20/assets/150933246/30319027-f53e-4f98-93b6-57aceacd9d07)

**E. User**

User dapat mengubah informasi profil mereka, user yang di ban tidak dapat masuk kedalam channel dan dapat keluar dari room, channel, atau keluar sepenuhnya dari DiscorIT.

![image](https://github.com/Faridaqurr/Sisop-FP-2024-MH-IT20/assets/150933246/a23eb0c4-2beb-4eae-b396-2ce6fbaebc30)

![image](https://github.com/Faridaqurr/Sisop-FP-2024-MH-IT20/assets/150933246/80c60618-2717-4ea1-a523-0e02429a781c)

![image](https://github.com/Faridaqurr/Sisop-FP-2024-MH-IT20/assets/150933246/a2193ead-bc19-42c0-a16c-dc297879a70a)

![image](https://github.com/Faridaqurr/Sisop-FP-2024-MH-IT20/assets/150933246/1ecbf173-0d4d-4d5e-80de-24e87c360a7b)

**F. Error Handling**

Jika ada command yang tidak sesuai penggunaannya. Maka akan mengeluarkan pesan error dan tanpa keluar dari program client.

**G. Monitor**
  - User dapat menampilkan isi chat secara real-time menggunakan program monitor. Jika ada perubahan pada isi chat, perubahan tersebut akan langsung ditampilkan di terminal.
  
  - Sebelum dapat menggunakan monitor, pengguna harus login terlebih dahulu dengan cara yang mirip seperti login di DiscorIT.
  
  - Untuk keluar dari room dan menghentikan program monitor dengan perintah "EXIT".
  
  - Monitor dapat digunakan untuk menampilkan semua chat pada room, mulai dari chat pertama hingga chat yang akan datang nantinya.

![image](https://github.com/Faridaqurr/Sisop-FP-2024-MH-IT20/assets/150933246/9fc05165-da43-4f37-8dbc-d26cd365b4c4)

### Changelog

  - [13/06/2024] menambahkan penjelasan pada bagian Bagaimana Program Diakses

## Hasil Pengerjaan

## discorit.c
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024
#define MAX_NAME_LENGTH 50

void handle_commands(int sock, const char *username) {
    char buffer[BUF_SIZE] = {0};
    char channel[MAX_NAME_LENGTH] = {0};
    char room[MAX_NAME_LENGTH] = {0};
    int key_prompt = 0;
    int in_channel = 0;
    int in_room = 0;

    while (1) {
        if (key_prompt) {
            printf("Key: ");
            fflush(stdout);
            key_prompt = 0;
        } else if (in_channel && in_room) {
            printf("[%s/%s/%s] ", username, channel, room);
        } else if (in_channel) {
            printf("[%s/%s] ", username, channel);
        } else {
            printf("[%s] ", username);
        }

        if (fgets(buffer, BUF_SIZE, stdin) == NULL) {
            break;
        }
        buffer[strcspn(buffer, "\n")] = 0;

        if (strcmp(buffer, "EXIT") == 0) {
            send(sock, buffer, strlen(buffer), 0);
            if (in_room) {
                in_room = 0;
                memset(room, 0, sizeof(room));
            } else if (in_channel) {
                in_channel = 0;
                memset(channel, 0, sizeof(channel));
            } else {
                break;
            }
        } else {
            char command[BUF_SIZE] = {0};
            char name[MAX_NAME_LENGTH] = {0};

            if (sscanf(buffer, "%s %s", command, name) == 2 && strcmp(command, "JOIN") == 0) {
                if (in_channel && !in_room) {
                    snprintf(room, sizeof(room), "%s", name);
                    in_room = 1;
                } else if (!in_channel) {
                    snprintf(channel, sizeof(channel), "%s", name);
                    in_channel = 1;
                }
            }

            if (send(sock, buffer, strlen(buffer), 0) == -1) {
                perror("Send failed");
                break;
            }
        }

        memset(buffer, 0, sizeof(buffer));
        int bytes_read = read(sock, buffer, BUF_SIZE - 1);
        if (bytes_read <= 0) {
            perror("Read failed");
            break;
        }
        buffer[bytes_read] = '\0';

        if (strstr(buffer, "masuk channel")) {
            char *channel_name = strstr(buffer, "bergabung dengan channel ") + strlen("bergabung dengan channel ");
            strncpy(channel, channel_name, sizeof(channel) - 1);
            channel[sizeof(channel) - 1] = '\0';
            in_channel = 1;
        } else if (strstr(buffer, "masuk room")) {
            char *room_name = strstr(buffer, "bergabung dengan room ") + strlen("bergabung dengan room ");
            strncpy(room, room_name, sizeof(room) - 1);
            room[sizeof(room) - 1] = '\0';
            in_room = 1;
        } else if (strstr(buffer, "Key:")) {
            key_prompt = 1;
        }

        printf("%s\n", buffer);
    }
}

int main(int argc, char const *argv[]) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUF_SIZE] = {0};

    if (argc < 5) {
        printf("Usage: ./discorit REGISTER/LOGIN username -p password\n");
        return 1;
    }

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        return 1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        return 1;
    }

    if (strcmp(argv[1], "REGISTER") == 0 && strcmp(argv[3], "-p") == 0) {
        snprintf(buffer, BUF_SIZE, "REGISTER %s -p %s", argv[2], argv[4]);
    } else if (strcmp(argv[1], "LOGIN") == 0 && strcmp(argv[3], "-p") == 0) {
        snprintf(buffer, BUF_SIZE, "LOGIN %s -p %s", argv[2], argv[4]);
    } else {
        printf("Invalid command\n");
        close(sock);
        return 1;
    }

    send(sock, buffer, strlen(buffer), 0);
    memset(buffer, 0, sizeof(buffer));
    int bytes_read = read(sock, buffer, BUF_SIZE - 1);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        printf("%s\n", buffer);
        if (strstr(buffer, "Login successful") != NULL || strstr(buffer, "Registered successfully") != NULL) {
            handle_commands(sock, argv[2]);
        }
    }

    close(sock);
    return 0;
}
```
1. Library dan Konstanta

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024
#define MAX_NAME_LENGTH 50
```

Pada code tersebut kami menggunakan beberapa library dengan kegunaan sebagai berikut :
- `stdio.h` untuk input dan output.
- `stdlib.h` untuk fungsi umum seperti exit().
- `string.h` untuk manipulasi string.
- `unistd.h` untuk fungsi POSIX seperti read() dan write().
- `arpa/inet.h` untuk fungsi terkait jaringan seperti inet_pton().

Serta berikut beberapa konstanta yang kami gunakan beserta kegunaannya :
- `PORT` menentukan port yang digunakan untuk koneksi jaringan.
- `BUF_SIZE` menentukan ukuran buffer untuk pengiriman dan penerimaan data.
- `MAX_NAME_LENGTH` menentukan panjang maksimum nama channel atau room.

2. `void handle_commands`

```
void handle_commands(int sock, const char *username) {
    char buffer[BUF_SIZE] = {0};
    char channel[MAX_NAME_LENGTH] = {0};
    char room[MAX_NAME_LENGTH] = {0};
    int key_prompt = 0;
    int in_channel = 0;
    int in_room = 0;

    while (1) {
        if (key_prompt) {
            printf("Key: ");
            fflush(stdout);
            key_prompt = 0;
        } else if (in_channel && in_room) {
            printf("[%s/%s/%s] ", username, channel, room);
        } else if (in_channel) {
            printf("[%s/%s] ", username, channel);
        } else {
            printf("[%s] ", username);
        }

        if (fgets(buffer, BUF_SIZE, stdin) == NULL) {
            break;
        }
        buffer[strcspn(buffer, "\n")] = 0;

        if (strcmp(buffer, "EXIT") == 0) {
            send(sock, buffer, strlen(buffer), 0);
            if (in_room) {
                in_room = 0;
                memset(room, 0, sizeof(room));
            } else if (in_channel) {
                in_channel = 0;
                memset(channel, 0, sizeof(channel));
            } else {
                break;
            }
        } else {
            char command[BUF_SIZE] = {0};
            char name[MAX_NAME_LENGTH] = {0};

            if (sscanf(buffer, "%s %s", command, name) == 2 && strcmp(command, "JOIN") == 0) {
                if (in_channel && !in_room) {
                    snprintf(room, sizeof(room), "%s", name);
                    in_room = 1;
                } else if (!in_channel) {
                    snprintf(channel, sizeof(channel), "%s", name);
                    in_channel = 1;
                }
            }

            if (send(sock, buffer, strlen(buffer), 0) == -1) {
                perror("Send failed");
                break;
            }
        }

        memset(buffer, 0, sizeof(buffer));
        int bytes_read = read(sock, buffer, BUF_SIZE - 1);
        if (bytes_read <= 0) {
            perror("Read failed");
            break;
        }
        buffer[bytes_read] = '\0';

        if (strstr(buffer, "masuk channel")) {
            char *channel_name = strstr(buffer, "bergabung dengan channel ") + strlen("bergabung dengan channel ");
            strncpy(channel, channel_name, sizeof(channel) - 1);
            channel[sizeof(channel) - 1] = '\0';
            in_channel = 1;
        } else if (strstr(buffer, "masuk room")) {
            char *room_name = strstr(buffer, "bergabung dengan room ") + strlen("bergabung dengan room ");
            strncpy(room, room_name, sizeof(room) - 1);
            room[sizeof(room) - 1] = '\0';
            in_room = 1;
        } else if (strstr(buffer, "Key:")) {
            key_prompt = 1;
        }

        printf("%s\n", buffer);
    }
}
```

Function atau void tersebut berfungsi untuk menangani interaksi pengguna setelah berhasil mendaftar atau login dan membaca perintah dari pengguna, mengirim perintah ke server, dan menangani respons dari server.

3. `main`

```
int main(int argc, char const *argv[]) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUF_SIZE] = {0};

    if (argc < 5) {
        printf("Usage: ./discorit REGISTER/LOGIN username -p password\n");
        return 1;
    }

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        return 1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        return 1;
    }

    if (strcmp(argv[1], "REGISTER") == 0 && strcmp(argv[3], "-p") == 0) {
        snprintf(buffer, BUF_SIZE, "REGISTER %s -p %s", argv[2], argv[4]);
    } else if (strcmp(argv[1], "LOGIN") == 0 && strcmp(argv[3], "-p") == 0) {
        snprintf(buffer, BUF_SIZE, "LOGIN %s -p %s", argv[2], argv[4]);
    } else {
        printf("Invalid command\n");
        close(sock);
        return 1;
    }

    send(sock, buffer, strlen(buffer), 0);
    memset(buffer, 0, sizeof(buffer));
    int bytes_read = read(sock, buffer, BUF_SIZE - 1);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        printf("%s\n", buffer);
        if (strstr(buffer, "Login successful") != NULL || strstr(buffer, "Registered successfully") != NULL) {
            handle_commands(sock, argv[2]);
        }
    }

    close(sock);
    return 0;
}
```

Fungsi `main` yang ada pada code `discorit.c` tersebut berfungsi sebagai fungsi utama program, dimana ia mengatur koneksi ke server dan memulai proses login atau pendaftaran. Selain itu, ia juga memeriksa argumen, membuat socket, dan mengirim perintah register/login


## monitor.c

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>

#define PORT 8080
#define BUF_SIZE 1024
#define DISCORIT_DIR "/home/revalina/final_project"
#define MAX_CLIENTS 100

typedef struct {
    int socket;
    char username[BUF_SIZE];
    char channel[BUF_SIZE];
    char room[BUF_SIZE];
} client_t;

client_t *clients[MAX_CLIENTS];
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

void add_client(client_t *cl) {
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (!clients[i]) {
            clients[i] = cl;
            break;
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void remove_client(int socket) {
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i]) {
            if (clients[i]->socket == socket) {
                clients[i] = NULL;
                break;
            }
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void broadcast_message(const char *channel, const char *room, const char *message, int sender_socket) {
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i]) {
            if (strcmp(clients[i]->channel, channel) == 0 && strcmp(clients[i]->room, room) == 0) {
                if (clients[i]->socket != sender_socket) {
                    send(clients[i]->socket, message, strlen(message), 0);
                }
            }
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void *handle_client(void *arg) {
    char buffer[BUF_SIZE];
    char username[BUF_SIZE];
    char channel[BUF_SIZE];
    char room[BUF_SIZE];
    int leave_flag = 0;

    client_t *cli = (client_t *)arg;

    // Handle initial login or registration
    int bytes_received = recv(cli->socket, buffer, BUF_SIZE, 0);
    buffer[bytes_received] = '\0';

    if (strncmp(buffer, "LOGIN ", 6) == 0 || strncmp(buffer, "REGISTER ", 9) == 0) {
        // Extract username
        sscanf(buffer, "%*s %s -p %*s", username);
        strcpy(cli->username, username);

        if (strncmp(buffer, "LOGIN ", 6) == 0) {
            // Assume login is always successful for simplicity
            snprintf(buffer, BUF_SIZE, "Login successful\n");
        } else {
            snprintf(buffer, BUF_SIZE, "Registered successfully\n");
        }

        send(cli->socket, buffer, strlen(buffer), 0);
    }

    while (1) {
        if (leave_flag) {
            break;
        }

        memset(buffer, 0, BUF_SIZE);
        int bytes_received = recv(cli->socket, buffer, BUF_SIZE, 0);
        buffer[bytes_received] = '\0';

        if (strcmp(buffer, "EXIT") == 0) {
            leave_flag = 1;
        } else if (sscanf(buffer, "JOIN %s", channel) == 1) {
            strcpy(cli->channel, channel);
            snprintf(buffer, BUF_SIZE, "bergabung dengan channel %s\n", channel);
            send(cli->socket, buffer, strlen(buffer), 0);
        } else if (sscanf(buffer, "JOIN %s %s", channel, room) == 2) {
            strcpy(cli->channel, channel);
            strcpy(cli->room, room);
            snprintf(buffer, BUF_SIZE, "bergabung dengan room %s\n", room);
            send(cli->socket, buffer, strlen(buffer), 0);

            // Monitor the chat file
            char file_path[BUF_SIZE];
            snprintf(file_path, sizeof(file_path), "%s/%s/%s/chat.csv", DISCORIT_DIR, channel, room);

            FILE *file = fopen(file_path, "a");
            if (file) {
                time_t now = time(NULL);
                struct tm *t = localtime(&now);
                char time_str[20];
                strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", t);
                fprintf(file, "INFO,%s,%s bergabung dengan room\n", time_str, cli->username);
                fclose(file);
            }
        } else {
            // Broadcast message to other clients in the same channel and room
            snprintf(buffer + strlen(buffer), BUF_SIZE - strlen(buffer), " [%s]: %s", cli->username, buffer);
            broadcast_message(cli->channel, cli->room, buffer, cli->socket);
        }
    }

    // Client disconnects
    close(cli->socket);
    remove_client(cli->socket);
    free(cli);

    return NULL;
}

int main() {
    int listen_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    pthread_t tid;

    // Initialize the server socket
    listen_socket = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(listen_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(listen_socket, 10);

    printf("Server listening on port %d\n", PORT);

    while (1) {
        client_socket = accept(listen_socket, (struct sockaddr *)&client_addr, &client_len);

        // Create a client struct
        client_t *cli = (client_t *)malloc(sizeof(client_t));
        cli->socket = client_socket;
        memset(cli->username, 0, BUF_SIZE);
        memset(cli->channel, 0, BUF_SIZE);
        memset(cli->room, 0, BUF_SIZE);

        // Add client to the clients array
        add_client(cli);

        // Create a thread to handle the client
        pthread_create(&tid, NULL, &handle_client, (void *)cli);
        pthread_detach(tid);
    }

    return 0;
}
```

1. Header / LIbrary

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>
```

Berikut beberapa header atau library yang kami gunakan dalam code `monitor.c` ini :
- `stdio.h`: Digunakan untuk fungsi input/output seperti printf, sprintf, snprintf, dll.
- `stdlib.h`: Digunakan untuk fungsi standar seperti malloc, free, exit, dll.
- `string.h`: Digunakan untuk fungsi manipulasi string seperti strcpy, strcmp, strlen, dll.
- `unistd.h`: Digunakan untuk fungsi POSIX seperti close, read, write, sleep, dll.
- `arpa/inet.h`: Digunakan untuk fungsi dan struktur terkait jaringan seperti sockaddr_in, inet_addr, dll.
- `pthread.h`: Digunakan untuk fungsi threading POSIX seperti pthread_create, pthread_mutex_lock, dll.
- `sys/stat.h`: Digunakan untuk fungsi terkait status file seperti mkdir, stat, dll.
- `time.h`: Digunakan untuk fungsi waktu seperti time, localtime, strftime, dll.

2. Konstanta

```
#define PORT 8080
#define BUF_SIZE 1024
#define DISCORIT_DIR "/home/revalina/final_project"
#define MAX_CLIENTS 100
```

Berikut beberapa konstanta yang kami gunakan dalam code `monitor.c` ini :
- `PORT`: Port server mendengarkan koneksi.
- `BUF_SIZE`: Ukuran buffer yang digunakan untuk membaca/mengirim data.
- `DISCORIT_DIR`: Direktori dasar untuk menyimpan file chat.
- `MAX_CLIENTS`: Jumlah maksimal klien yang bisa terhubung.

3. `void add_client(client_t *cl)`

```
void add_client(client_t *cl) {
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (!clients[i]) {
            clients[i] = cl;
            break;
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}
```

berfungsi untuk menambahkan klien ke array clients dengan menggunakan mutex untuk memastikan thread-safety.

3. `void remove_client(int socket):`

```
void remove_client(int socket) {
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i]) {
            if (clients[i]->socket == socket) {
                clients[i] = NULL;
                break;
            }
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}
```

berfungsi untuk menghapus klien dari array clients berdasarkan socket-nya.

4. `void broadcast_message(const char *channel, const char *room, const char *message, int sender_socket)`

```
void broadcast_message(const char *channel, const char *room, const char *message, int sender_socket) {
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i]) {
            if (strcmp(clients[i]->channel, channel) == 0 && strcmp(clients[i]->room, room) == 0) {
                if (clients[i]->socket != sender_socket) {
                    send(clients[i]->socket, message, strlen(message), 0);
                }
            }
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}
```

berfungsi untuk mengirim pesan ke semua klien di channel dan room yang sama kecuali pengirim.

5. `void handle_client(void *arg)`

```
void *handle_client(void *arg) {
    char buffer[BUF_SIZE];
    char username[BUF_SIZE];
    char channel[BUF_SIZE];
    char room[BUF_SIZE];
    int leave_flag = 0;

    client_t *cli = (client_t *)arg;

    // Handle initial login or registration
    int bytes_received = recv(cli->socket, buffer, BUF_SIZE, 0);
    buffer[bytes_received] = '\0';

    if (strncmp(buffer, "LOGIN ", 6) == 0 || strncmp(buffer, "REGISTER ", 9) == 0) {
        // Extract username
        sscanf(buffer, "%*s %s -p %*s", username);
        strcpy(cli->username, username);

        if (strncmp(buffer, "LOGIN ", 6) == 0) {
            // Assume login is always successful for simplicity
            snprintf(buffer, BUF_SIZE, "Login successful\n");
        } else {
            snprintf(buffer, BUF_SIZE, "Registered successfully\n");
        }

        send(cli->socket, buffer, strlen(buffer), 0);
    }

    while (1) {
        if (leave_flag) {
            break;
        }

        memset(buffer, 0, BUF_SIZE);
        int bytes_received = recv(cli->socket, buffer, BUF_SIZE, 0);
        buffer[bytes_received] = '\0';

        if (strcmp(buffer, "EXIT") == 0) {
            leave_flag = 1;
        } else if (sscanf(buffer, "JOIN %s", channel) == 1) {
            strcpy(cli->channel, channel);
            snprintf(buffer, BUF_SIZE, "bergabung dengan channel %s\n", channel);
            send(cli->socket, buffer, strlen(buffer), 0);
        } else if (sscanf(buffer, "JOIN %s %s", channel, room) == 2) {
            strcpy(cli->channel, channel);
            strcpy(cli->room, room);
            snprintf(buffer, BUF_SIZE, "bergabung dengan room %s\n", room);
            send(cli->socket, buffer, strlen(buffer), 0);

            // Monitor the chat file
            char file_path[BUF_SIZE];
            snprintf(file_path, sizeof(file_path), "%s/%s/%s/chat.csv", DISCORIT_DIR, channel, room);

            FILE *file = fopen(file_path, "a");
            if (file) {
                time_t now = time(NULL);
                struct tm *t = localtime(&now);
                char time_str[20];
                strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", t);
                fprintf(file, "INFO,%s,%s bergabung dengan room\n", time_str, cli->username);
                fclose(file);
            }
        } else {
            // Broadcast message to other clients in the same channel and room
            snprintf(buffer + strlen(buffer), BUF_SIZE - strlen(buffer), " [%s]: %s", cli->username, buffer);
            broadcast_message(cli->channel, cli->room, buffer, cli->socket);
        }
    }

    // Client disconnects
    close(cli->socket);
    remove_client(cli->socket);
    free(cli);

    return NULL;
}
```

berfungsi untuk menangani komunikasi dengan klien

6. `main`

```
int main() {
    int listen_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    pthread_t tid;

    // Initialize the server socket
    listen_socket = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(listen_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(listen_socket, 10);

    printf("Server listening on port %d\n", PORT);

    while (1) {
        client_socket = accept(listen_socket, (struct sockaddr *)&client_addr, &client_len);

        // Create a client struct
        client_t *cli = (client_t *)malloc(sizeof(client_t));
        cli->socket = client_socket;
        memset(cli->username, 0, BUF_SIZE);
        memset(cli->channel, 0, BUF_SIZE);
        memset(cli->room, 0, BUF_SIZE);

        // Add client to the clients array
        add_client(cli);

        // Create a thread to handle the client
        pthread_create(&tid, NULL, &handle_client, (void *)cli);
        pthread_detach(tid);
    }

    return 0;
}
```

berfungsi untuk inisialisasi server socket dan menerima koneksi klien

## server.c

```
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
#define USER_FILE "/home/revalina/final_project/users.csv"
#define DISCORIT_DIR "/home/revalina/final_project"
#define CHANNEL_FILE "/home/revalina/final_project/channels.csv"

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
    while ((client_sock = accept(socket_desc, (struct sockaddr )&client, (socklen_t)&c))) {
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
        sscanf(line, "%d,%[^,],%[^,],%*s", username);
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
        sscanf(line, "%d,%[^,],%[^,],%*s", stored_username);
        
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
    int sock = (int)socket_desc;
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
```
1. `main`

```
int main(int argc, char *argv[]) {
    //daemonize(); // Optional daemonize call

    int socket_desc, client_sock, c, *new_sock;
    struct sockaddr_in server, client;

    // Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Could not create socket");
    }
    puts("Socket created");

    // Set socket options
    if(setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0) {
        perror("setsockopt(SO_REUSEADDR) failed");
        return 1;
    }
    if (setsockopt(socket_desc, SOL_SOCKET, SO_REUSEPORT, &(int){1}, sizeof(int)) < 0) {
        perror("setsockopt(SO_REUSEPORT) failed");
        return 1;
    }

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // Bind the socket
    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");

    // Listen for connections
    listen(socket_desc, 3);

    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);

    // Accept incoming connections
    while ((client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c))) {
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
```

berfungsi untuk membuat socket, mengikat (bind) socket ke alamat dan port tertentu, mendengarkan (listen) koneksi masuk, dan menerima (accept) koneksi dari client. Selain itu `main` ini juga memulai thread baru untuk setiap koneksi yang diterima menggunakan pthread_create.

2. `Daemonize`

```
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
```

berfungsi untuk mengubah proses menjadi daemon dengan cara fork dua kali dan mengatur beberapa pengaturan proses seperti umask dan direktori kerja.

3. `void Connection Handler `

```
void *connection_handler(void *socket_desc) {
    int sock = *(int *)socket_desc;
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

    while ((read_size = recv(sock, client_message, BUF_SIZE, 0)) > 0) {
        client_message[read_size] = '\0';
        char username[BUF_SIZE], password[BUF_SIZE], command[BUF_SIZE];
        sscanf(client_message, "%s %s -p %s", command, username, password);

        if (strcmp(command, "REGISTER") == 0) {
            handle_register(username, password);
            send(sock, "Registration successful\n", 24, 0);
        } else if (strcmp(command, "LOGIN") == 0) {
            int login_result = handle_login(username, password, &clients[client_index]);
            if (login_result) {
                send(sock, "Login successful\n", 18, 0);
            } else {
                send(sock, "Login failed\n", 13, 0);
            }
        } else if (clients[client_index].is_logged_in) {
            char channel_name[BUF_SIZE], key[BUF_SIZE];

            if (sscanf(client_message, "CREATE CHANNEL %s -k %s", channel_name, key) == 2) {
                int result = create_channel(channel_name, key, &clients[client_index]);
                if (result) {
                    send(sock, "Channel created successfully\n", 29, 0);
                } else {
                    send(sock, "Failed to create channel\n", 25, 0);
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
                send(sock, "Invalid command\n", 16, 0);
            }
        } else {
            send(sock, "Invalid command\n", 16, 0);
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
```

berfungsi untuk menangani koneksi klien dengan membaca pesan yang diterima dan memprosesnya berdasarkan perintah yang dikirim oleh klien dan menjalankan fungsi yang sesuai (misalnya, handle_register, handle_login, create_channel, dll.) berdasarkan perintah klien.

4. `void Handle Register`

```
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
```

berfungsi untuk menangani proses registrasi pengguna baru dengan memeriksa apakah username sudah terdaftar, kemudian menyimpan username, password yang di-hash, dan peran pengguna dalam file .csv

5. `void Handle Login`

```
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
            char *salt = strtok(stored_password, "$");
            salt = strtok(NULL, "$");
            char *hashed_input_password = crypt(password, salt);
            if (hashed_input_password && strcmp(stored_password, hashed_input_password) == 0) {
                client->username = strdup(username);
                client->role = strdup(stored_role);
                client->is_logged_in = 1;
                fclose(fp);
                return 1;
            }
        }
    }

    fclose(fp);
    return 0;
}
```

berfungsi untuk menangani proses login pengguna dengan memverifikasi username dan password yang diberikan terhadap data yang disimpan dalam file .csv

6. `void Edit User `

```
void edit_user(char *username, char *new_username, char *new_password, int sock) {
    FILE *fp = fopen(USER_FILE, "r+");
    if (fp == NULL) {
        perror("Unable to open users.csv");
        send(sock, "Failed to edit user\n", 19, 0);
        return;
    }

    FILE *temp_fp = fopen("temp.csv", "w");
    if (temp_fp == NULL) {
        perror("Unable to open temp.csv");
        fclose(fp);
        send(sock, "Failed to edit user\n", 19, 0);
        return;
    }

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), fp)) {
        char stored_username[BUF_SIZE], stored_password[BUF_SIZE], stored_role[BUF_SIZE];
        int id;
        sscanf(line, "%d,%[^,],%[^,],%s", &id, stored_username, stored_password, stored_role);

        if (strcmp(stored_username, username) == 0) {
            found = 1;
            if (new_username != NULL) {
                strcpy(stored_username, new_username);
            }
            if (new_password != NULL) {
                char salt[SALT_LENGTH + 1];
                for (int i = 0; i < SALT_LENGTH; i++) {
                    salt[i] = 'A' + (random() % 26);
                }
                salt[SALT_LENGTH] = '\0';
                char *hashed_password = crypt(new_password, salt);
                if (hashed_password != NULL) {
                    strcpy(stored_password, hashed_password);
                }
            }
        }
        fprintf(temp_fp, "%d,%s,%s,%s\n", id, stored_username, stored_password, stored_role);
    }

    fclose(fp);
    fclose(temp_fp);

    if (found) {
        remove(USER_FILE);
        rename("temp.csv", USER_FILE);
        send(sock, "User edited successfully\n", 25, 0);
    } else {
        remove("temp.csv");
        send(sock, "User not found\n", 15, 0);
    }
}
```

berfungsi untuk menangani proses pengeditan informasi pengguna (username dan/atau password) dalam file .csv

7. `void List Users`

```
void list_users(int sock) {
    FILE *fp = fopen(USER_FILE, "r");
    if (fp == NULL) {
        perror("Unable to open users.csv");
        send(sock, "Failed to list users\n", 19, 0);
        return;
    }

    char line[256];
    char buffer[BUF_SIZE] = "Users:\n";
    while (fgets(line, sizeof(line), fp)) {
        char stored_username[BUF_SIZE], stored_password[BUF_SIZE], stored_role[BUF_SIZE];
        int id;
        sscanf(line, "%d,%[^,],%[^,],%s", &id, stored_username, stored_password, stored_role);
        strcat(buffer, stored_username);
        strcat(buffer, "\n");
    }

    fclose(fp);
    send(sock, buffer, strlen(buffer), 0);
}
```

berfungsi untuk menangani proses daftar pengguna dengan mengirimkan daftar semua username yang ada dalam file .csv kepada klien

### Proses
1. Register dan Login

![WhatsApp Image 2024-06-28 at 10 59 35 PM](https://github.com/Faridaqurr/Sisop-FP-2024-MH-IT20/assets/150936800/ba424cb9-0cb6-40e3-aed4-ae2169cce691)

![WhatsApp Image 2024-06-28 at 11 00 10 PM](https://github.com/Faridaqurr/Sisop-FP-2024-MH-IT20/assets/150936800/9161f09f-94b4-40de-93d9-6a086ebc71a1)

2. Mengidentifikasi role

![WhatsApp Image 2024-06-28 at 11 00 45 PM](https://github.com/Faridaqurr/Sisop-FP-2024-MH-IT20/assets/150936800/a29cb57c-80b3-4ea0-9003-86db46a88362)

3. Penggunaan Root

![WhatsApp Image 2024-06-28 at 11 06 14 PM](https://github.com/Faridaqurr/Sisop-FP-2024-MH-IT20/assets/150936800/c89e4dd3-1e94-4ac2-8e8b-fe3452f1a8bb)

4. Connecting Port

![WhatsApp Image 2024-06-28 at 11 07 32 PM](https://github.com/Faridaqurr/Sisop-FP-2024-MH-IT20/assets/150936800/de42853e-619a-4e31-b457-0e123c89a861)


##Revisi
