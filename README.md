# Analisa Data Dalam Dota2

struct Vec{

    int x,y,z;
    
};

struct Snd{

    uint16_t id_player;
    Vec pos;
    uint32_t id_karakter;
    char action[512];

};

struktur data diatas merupakan asumsi dari data yang dikirim oleh client ke server dalam game dota2
struktur data tersebut kemudian dikirim kembali ke client lain

#Penjelasan Program
1. Data struct tersebut dipacking ke dalam char*
2. Client mengirim data yang sudah dipacking ke server
3. Server menerima data tersebut dan unpacking ke dalam bentuk data struct
4. library yang digunakan adalah winsock2 yang mana pengiriman datanya menggunakan const char*
5. untuk packing struct ke char* menggunakan memcpy() dalam c++.


#Update
1. type char* to unsigned char* (byte*)
2. Data struct dari client di ubah ke byte* lalu di kirim ke server
3. Server menerima data byte* kemudian diubah kembali ke data struct lalu data struct dirubah kembali ke byte* dan dikirim ke client
4. Winsock menggunakan char* untuk mengirim data sehingga untuk mengubah byte* ke char* dan sebaliknya perlu menggunakan reinterpret_cast (fungsi c++ untuk mengubah pointer dari type data apapun ke poninter type data lain)