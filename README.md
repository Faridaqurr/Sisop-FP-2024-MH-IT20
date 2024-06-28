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

###discorit.c
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
