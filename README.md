# Soal Final Project

**A. Autentikasi**
  - Setiap user harus memiliki username dan password untuk mengakses DiscorIT. Username, password, dan global role disimpan dalam file user.csv.
  
  - Jika tidak ada user lain dalam sistem, user pertama yang mendaftar otomatis mendapatkan role "ROOT". Username harus bersifat unique dan password wajib di encrypt menggunakan menggunakan bcrypt.

![image](https://github.com/Faridaqurr/Sisop-FP-2024-MH-IT20/assets/150933246/de6c0c9a-2a90-4ec4-8866-005e8805d555)

![image](https://github.com/Faridaqurr/Sisop-FP-2024-MH-IT20/assets/150933246/26630e2c-8033-4b3e-bd50-dfa356ae932e)

**B. Bagaimana DiscorIT digunakan**

  **Perbedaan Akses antara Root, Admin, dan User :**
  - Root: Memiliki akses penuh untuk mengelola semua channel, room, dan user. Root adalah akun yang pertama kali mendaftar.
    
  - Admin: Memiliki akses untuk mengelola channel dan room yang mereka buat, serta mengelola user dalam channel mereka.
  
  - User: Dapat mengirim pesan chat, melihat channel, dan room. user menjadi admin di channel yang mereka buat.


![image](https://github.com/Faridaqurr/Sisop-FP-2024-MH-IT20/assets/150933246/810f1a95-797d-4b16-9654-20317b052d23)

**Setelah Masuk Channel user dapat melihat list room dan pengguna dalam channel tersebut**

![image](https://github.com/Faridaqurr/Sisop-FP-2024-MH-IT20/assets/150933246/e9cb7d5c-af1e-427d-ba76-f5d92c8eeb2e)

![image](https://github.com/Faridaqurr/Sisop-FP-2024-MH-IT20/assets/150933246/ffaff174-1b6d-4c28-a0dd-ff4607be533c)

Ketika user pertama kali masuk ke channel, mereka memiliki akses terbatas. Jika mereka telah masuk sebelumnya, akses mereka meningkat sesuai dengan admin dan root.

![image](https://github.com/Faridaqurr/Sisop-FP-2024-MH-IT20/assets/150933246/9b3d92f3-4e69-477c-a56f-1bad5c8e5fd2)

User dapat masuk ke room setelah bergabung dengan channel.

![image](https://github.com/Faridaqurr/Sisop-FP-2024-MH-IT20/assets/150933246/439e2a31-53e9-4060-88f7-f98c07b69dee)

![image](https://github.com/Faridaqurr/Sisop-FP-2024-MH-IT20/assets/150933246/14ee72c3-c9a9-4b2c-afab-db3fa9419a99)
![image](https://github.com/Faridaqurr/Sisop-FP-2024-MH-IT20/assets/150933246/c0a38da0-19b3-4901-85e9-fc6dabfff80e)

**C. Root**
  - Akun yang pertama kali mendaftar otomatis mendapatkan peran "root".
  
  - Root dapat masuk ke channel manapun tanpa key dan create, update, dan delete pada channel dan room, mirip dengan admin [D].
  
  - Root memiliki kemampuan khusus untuk mengelola user, seperti: list, edit, dan Remove.

![image](https://github.com/Faridaqurr/Sisop-FP-2024-MH-IT20/assets/150933246/4ffdc5db-bee2-4bec-8310-601389b8930b)

**D. Admin Channel**
  - Setiap user yang membuat channel otomatis menjadi admin di channel tersebut. Informasi tentang user disimpan dalam file auth.csv.
  
  - Admin dapat create, update, dan delete pada channel dan room, serta dapat remove, ban, dan unban user di channel mereka.

![image](https://github.com/Faridaqurr/Sisop-FP-2024-MH-IT20/assets/150933246/106df332-a236-4636-bd17-d8ada5334957)

![image](https://github.com/Faridaqurr/Sisop-FP-2024-MH-IT20/assets/150933246/f7b01cbc-c29a-45b3-8dc6-7f17a78fb43a)
![image](https://github.com/Faridaqurr/Sisop-FP-2024-MH-IT20/assets/150933246/edd872df-ac43-4f67-9b2e-67703d860860)

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
