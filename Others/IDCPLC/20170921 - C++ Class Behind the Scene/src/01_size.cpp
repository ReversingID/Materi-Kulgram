/**
Berapa ukuran dari setiap tipe data primitif?
Bagaimana tipe ini berperan untuk membentuk struct / class?

Compile:
    $ g++ 01_size.cpp -o 01_size
Run:
    01_size
*/
#include <stdio.h>

// Empty class
/*
    Kelas
*/
class  KelasKosong { };
struct StrukturKosong { };

class KelasA
{
public:
    void greet()
    {
        printf("Halo dari kelas!");
    }
};

struct StrukturA
{
    void greet()
    {
        printf("Halo dari struktur!");
    }
};

class KelasB 
{
public:
    int  tipe_data_int;
    long tipe_data_long;
};

struct StrukturB
{
    int  tipe_data_int;
    long tipe_data_long;
};

int main()
{
    KelasA    kelas;
    StrukturA struktur;

    KelasKosong    kelas_kosong;
    StrukturKosong struktur_kosong;

    KelasB    kelas_b;
    StrukturB struktur_b;

    printf("Tipe data primitif:\n");
    printf("sizeof(char)      = %d\n", sizeof(char));
    printf("sizeof(bool)      = %d\n", sizeof(bool));
    printf("sizeof(short)     = %d\n", sizeof(short));
    printf("sizeof(int)       = %d\n", sizeof(int));
    printf("sizeof(long)      = %d\n", sizeof(long));
    printf("sizeof(long long) = %d\n", sizeof(long long));
    printf("sizeof(float)     = %d\n", sizeof(float));
    printf("sizeof(double)    = %d\n", sizeof(double));

    printf("\n\n");
    printf("Class dan Struct:\n");
    printf("sizeof(kelas_kosong)    = %d\n", sizeof(kelas_kosong));
    printf("sizeof(struktur_kosong) = %d\n", sizeof(struktur_kosong));
    printf("Kelas di %p ukuran %d isinya? %x\n", &kelas, sizeof(kelas), kelas);
    printf("Struktur di %p ukuran %d isinya? %x\n", & struktur, sizeof(struktur), struktur);

    printf("\n\n");
    printf("Ukuran kelas dan komponennya:\n");
    printf("sizeof(kelas_b)    = %d\n", sizeof(kelas_b));
    printf("    [%p] sizeof(kelas_b.tipe_data_int)  = %d\n", &kelas_b.tipe_data_int, sizeof(kelas_b.tipe_data_int));
    printf("    [%p] sizeof(kelas_b.tipe_data_long) = %d\n", &kelas_b.tipe_data_long, sizeof(kelas_b.tipe_data_long));
    printf("sizeof(struktur_b) = %d\n", sizeof(struktur_b));
    printf("    [%p] sizeof(struktur_b.tipe_data_int)  = %d\n", &struktur_b.tipe_data_int, sizeof(struktur_b.tipe_data_int));
    printf("    [%p] sizeof(struktur_b.tipe_data_long) = %d\n", &struktur_b.tipe_data_long, sizeof(struktur_b.tipe_data_long));
    return 0;
}