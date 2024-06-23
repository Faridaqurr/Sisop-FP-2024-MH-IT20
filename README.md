# Soal Final Project

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
