# **LİBFT**

**#include “libft.h”**

**İÇİNDEKİLER**
=================

* [LIBFT](#libft)
   * [PROJENİN AMACI](#projenin-amacı)
   * [KAZANIMLAR](#kazanımlar)
      * [ARRAY-POINTER VE POİNTER ARİTMETİĞİ NEDİR](#array-pointer-ve-pointer-aritmetiği-nedir)
      * [ÇİFT BOYUTLU ARRAYS](#çift-boyutlu-arrays)
      * [MANİPÜLASYON (STR–MEM FONKSİYONLARININ TEMEL FARKI)](#manipülasyon-str-mem-fonksiyonlarının-temel-farkı)
      * [OVERLAP NEDİR?](#overlap-nedir)
      * [MALLOC (BELLEK ALANI TAHSİSİ)](#malloc-bellek-alanı-tahsisi)
      * [FD (FİLE DESCRİPTOR)](#fd-file-descriptor)
      * [TYPECAST (TÜR DÖNÜŞÜMÜ)](#typecast-tür-dönüşümü)
      * [STATİK FONKSİYON](#statik-fonksiyon)
      * [CONST TÜRÜNDEKİ DEĞİŞKENLER](#const-türünde-değişkenler)
      * [STRUCT VERİ YAPISI](#struct-veri-yapısı)
      * [BAĞLI LİSTE](#bağlı-liste)
   * [FONKSİYONLAR-İŞLEVLERİ](#fonksiyonlar-işlevleri)


## **PROJENİN AMACI**

Ecole 42'nin Libft projesi, öğrencilere algoritma geliştirme yetenekleri kazandırarak, temel işlevlerden başlayarak çeşitli algoritmik sorunları ele alma pratiği yapma fırsatı tanır. Ayrıca, geniş görevleri küçük ve yönetilebilir parçalara bölebilme becerisi kazanma şansı sunar. Projeler genellikle belirli kalite ve standartlara uymayı gerektirdiği için, öğrencilere temiz, okunabilir ve sürdürülebilir kod yazma alışkanlığı edinme imkanı sağlar. Ayrıca, öğrencilere kendi ihtiyaçlarına uygun özel çözümler üretme esnekliği tanıyarak, yaratıcılıklarını kullanmalarına olanak verir. Yazılan kütüphane, başka projelerde tekrar kullanılabilir olma özelliği ile öğrencilere kodlarını daha etkili bir şekilde yönetme yeteneği kazandırır. Sonuç olarak, Libft projesi öğrencilere programlama deneyimleri kazandırarak, daha karmaşık projelerle başa çıkmalarına ve yazılım geliştirme süreçlerinde daha etkili olmalarına katkı sağlar.

## **KAZANIMLAR**

### **ARRAY-POİNTER VE POİNTER ARİTMETİĞİ NEDİR**

**Dizeler(Arrays):**
Aynı türdeki verileri tutan sıralı bellek bloklarıdır. Örneğin, bir dizi içinde birden çok integer veya karakter tutabilirsiniz. Dizi elemanları, sıfırdan başlayarak indekslenir. Örneğin, arr[0] bir dizinin ilk elemanını temsil eder.
int arr[5] = {1, 2, 3, 4, 5};

**Pointerlar:**
Bellekte bir değişkenin adresini tutan değişkenlerdir. Yani, bir değişkenin bellek adresini saklamak için kullanılırlar. Pointerlar, dinamik bellek yönetimi ile (mallo, calloc, realloc ve free fonksiyonlarını kullanarak yönetilen), fonksiyonlara referans geçme ve veri yapıları gibi birçok konuda kullanışlıdır.

```c
int x = 10;
int *ptr = &x; // x'in bellek adresini tutan bir pointer
printf("x: %d\n", *ptr); // ptr, x'in değerine ulaşmak için kullanılabilir.
```

**Pointer Aritmetiği:**
Bir pointer'ın adresini değiştirerek bellekte ileri veya geri hareket etme işlemidir. Bu, dizilerle birleştirildiğinde özellikle güçlü bir araçtır. Pointer aritmetiği, bellekteki veri yapısını dolaşma veya işaretçi aracılığıyla dizilere erişme gibi durumlarda kullanılır.

```c
int arr[5] = {1, 2, 3, 4, 5};
int *ptr = arr; // Dizinin ilk elemanının adresini tutan bir pointer
// Pointer aritmetiği ile dizi elemanlarına erişim
printf("%d\n", *(ptr + 2)); // 3
```

Bu örnek, ptr'nin adresini 2 kadar kaydırarak dizinin üçüncü elemanına erişir. Bu nedenle, pointer aritmetiği, dizilerle çalışırken daha esnek ve güçlü bir erişim sağlar. Unutulmamalıdır ki adres bir değiştiğinde her zaman adres+1 değerini almaz içindeki veri türünün büyüklüğü dikkate alınarak veri adresi artmış olur. Mesela bir char pointerda adresler arası ilerlemek istersek bir karakter boyutu kadar(1 byte) bir integer pointerda adresler arası ilerlemek için bir tam sayı boyutu kadar ilerleme sağlanır.(4 byte) Ancak, pointer aritmetiği kullanırken dikkatli olunmalı ve bellek sınırlarına dikkat edilmelidir, aksi takdirde istenmeyen sonuçlar ortaya çıkabilir.
Pointer kullanırken dikkat edilmesi gerek en önemli şeylerden biride pointer için bellekte bir alan tahsis(malloc, calloc, realloc) etmektir. Eğer pointer için yer tahsis etmezsek "Dangling pointer" (asılı pointer) ile karşı karşıya kalabiliriz buda segmentetion hatası ya da programın doğru çalışamaması ile sonuçlanabilir.

**Dangling pointer:**
Peki nedir dangling pointer açıklayalım: geçerli bir bellek adresine işaret etmeyen bir pointer anlamına gelir. Bu durum, bir pointerın daha önce tahsis edilmiş bir bellek bölgesine işaret ettiği, ancak bu bellek bölgesinin serbest bırakıldığı veya yeniden tahsis edildiği durumlarda ortaya çıkar. Ya da bellek bölgesinin hiç tahsis edilmediğinde önceden tahsis edilen alanlardan birini göstermesi durumunda ortaya çıkar. Dangling pointerlar, bellek erişim hatalarına ve program çökmesine neden olabilir.

### **ÇİFT BOYUTLU ARRAYS**
Çift boyutlu diziler (2D arrays), C dilinde iki indeksle indekslenmiş, tablo benzeri bir veri yapısıdır. Bu diziler genellikle matrisleri veya tablo benzeri veri yapılarını temsil etmek için kullanılır.

```c
#include <stdio.h>
#include <stdlib.h>
int main() {
    int rows = 3;
    int cols = 4;
    int** matris = (int**)malloc(rows * sizeof(int*));    // Satır işaretçileri için bellek tahsisi
    if (matris == NULL)
        return EXIT_FAILURE;
    for (int i = 0; i < rows; i++)
{
        matris[i] = (int*)malloc(cols * sizeof(int));    // Her bir satır için sütunların bellek tahsisi
        if (matris[i] == NULL)
    {
            perror("Bellek tahsisi başarısız.");
            for (int j = 0; j < i; j++) // Önceden tahsis edilen belleği serbest bırakma
                free(matris[j]);
            free(matris);
            return EXIT_FAILURE;
        }
    }
    int initial_values[3][4] =
{
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };    // Matrisin başlangıç değerleri ile doldurulması
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            matris[i][j] = initial_values[i][j];
    printf("Matris:\n");
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) {
            printf("%d \n ", matris[i][j]);    // Matrisin elemanlarının yazdırılması
    for (int i = 0; i < rows; i++)
        free(matris[i]); // Belleğin serbest bırakılması
    free(matris);
    return 0;
}
}
```

### **MANİPÜLASYON  (STR –MEM FONKSİYONLARININ TEMEL FARKI)**
"Manipülasyon", bir şeyi değiştirme veya etkileme anlamına gelir. Manipülasyon, genellikle veri üzerinde çeşitli işlemler yaparak istenen sonuca ulaşmayı sağlar.

**Dize Manipülasyonu:**
Dize manipülasyonu, karakter dizileri üzerinde gerçekleştirilen işlemleri ifade eder.
Bu işlemler, karakter dizilerini birleştirme, bölme, kopyalama, karşılaştırma, arama ve değiştirme gibi çeşitli operasyonları içerir.
Örneğin, C programlama dilinde strcpy fonksiyonu, bir karakter dizisini başka bir karakter dizisine kopyalamak için kullanılır. Bu, dize manipülasyonuna örnek teşkil eder.

**Bellek Manipülasyonu:**
Bellek manipülasyonu, bilgisayar belleği üzerinde gerçekleştirilen işlemleri ifade eder.
Bu işlemler, bellek alanlarını ayırma, kopyalama, taşıma, sıfırlama ve serbest bırakma gibi çeşitli operasyonları içerir.
Örneğin, C programlama dilinde memcpy fonksiyonu, bellek üzerinde belirli bir sayıda baytı bir yerden başka bir yere kopyalamak için kullanılır. Bu, bellek manipülasyonuna örnek teşkil eder.

### **OVERLAP NEDİR?**
Overlap, hafızada birden fazla nesnenin aynı alana denk gelmesi durumudur. Bu durum, veri bozulmasına ve hatalı sonuçlara yol açabilir.
Overlap, iki şekilde oluşabilir:

**1. Bellek Bloklarının Üst Üste Binmesi:**
Bir bellek bloğunun, başka bir bellek bloğunun bir kısmını veya tamamını kaplaması durumudur. Örneğin, bir diziyi kopyalarken kaynak dizinin ve hedef dizinin bellekteki konumları örtüşüyorsa overlap oluşabilir.

**2. Aynı Bellek Konumuna Farklı Değerlerin Atanması:**
Aynı bellek konumuna birden fazla değer atanması durumudur. Bu durum, programcının hatası sonucu oluşabilir.

**Overlap'in Olumsuz Etkileri:**
•	Veri bozulmasına ve hatalı sonuçlara yol açabilir.

•	Programın çökmesine neden olabilir.

•	Güvenlik açıklarına yol açabilir.

**Overlap'den Kaçınmak İçin Yapılabilecekler:**
•	Bellek ayırma işlemlerinde dikkatli olmak.

•	Kopyalama işlemlerinde kaynak ve hedef dizilerin bellekteki konumlarını kontrol etmek.

•	Pointer aritmetiğini dikkatli kullanmak.

•	Bellek hatalarını kontrol eden araçları kullanmak.

**Memcpy ve Overlap:**
memcpy, belleği kopyalamak için kullanılan bir C fonksiyonudur. memcpy, overlap'e karşı hassastır ve overlap oluştuğunda beklenmedik sonuçlara yol açabilir. Bu nedenle, memcpy kullanırken kaynak ve hedef dizilerin bellekteki konumlarını kontrol etmek önemlidir.

**Memmove ve Overlap:**
memmove, memcpy'e benzer şekilde belleği kopyalamak için kullanılan bir C fonksiyonudur. memmove, overlap'e karşı dayanıklıdır ve overlap oluştuğunda bile doğru şekilde çalışır. Bu nedenle, overlap riski olan durumlarda memmove kullanmak daha güvenlidir.

### **MALLOC (BELLEK ALANI TAHSİSİ)**
Malloc (memory allocation), C programlama dilinde dinamik bellek tahsis etmek için kullanılan bir standart kütüphane fonksiyonudur. Bu fonksiyon, çalışma zamanında belirli bir sayıda bellek alanı ayırmak için kullanılır. İşte malloc'ın çalışma mantığı:

**Bellek Alanı Ayırma:**
malloc, belirtilen byte sayısında bir bellek alanı tahsis eder.
Fonksiyon şu şekilde kullanılır: void* malloc(size_t size);
size parametresi, ayırmak istenen bellek alanının boyutunu belirtir.

**Başarılı Tahsis Durumu:**
Eğer bellek tahsisi başarılı olursa, malloc ayırdığı bellek alanının başlangıç adresini içeren bir işaretçi döndürür (void* türünde).
Bu işaretçi, ayrılan bellek alanını işaret eder ve kullanıcı bu işaretçi aracılığıyla bu alana erişebilir.

**Başarısız Tahsis Durumu:**
Eğer bellek tahsisi başarısız olursa (örneğin, yeterli serbest bellek yoksa), malloc NULL işaretçisi döndürür.
Bu durumu kontrol etmek önemlidir, çünkü başarısız tahsis durumunda bellek kullanılmamış ve NULL işaretçisi ile işaretlenmiş olacaktır.

**Bellek Kullanımı:**
Ayrılan bellek alanı genellikle dinamik olarak oluşturulan veri yapıları veya dizileri tutmak için kullanılır.
Bellek kullanımı tamamlandıktan sonra, ayrılan bellek alanının serbest bırakılması (free fonksiyonu ile) önemlidir. Serbest bırakılan alan yeniden kullanılabilir. Ayrılan bellek alanı serbest bırakılmadığı sürece, bellek sızıntıları ortaya çıkabilir.

**Bellek sızıntısı:**
Bir programın çalışma sürecinde tahsis edilen bellek bloklarının serbest bırakılmaması veya düzgün bir şekilde yönetilmemesi durumudur.
Bellek sızıntısı, programın bellek kullanımını kontrol etme yeteneğini kaybetmesine ve uzun süre çalıştığında sistem kaynaklarını tüketmesine neden olabilir. Bu durum, programın performansını düşürebilir ve hatta uygulamanın çökmesine neden olabilir. Bu yüzden kullandığımız dinamik bellekleri doğru bir şekilde serbest bırakmalı ve sonrasında işaretçimizi NULL e eşitlemeyi unutmamalıyız.

### **FD (FİLE DESCRİPTOR)**
fd,  dosya tanımlayıcısı (file descriptor) işletim sistemlerinde dosyaları, soketleri ve diğer giriş/çıkış kaynaklarını temsil etmek için kullanılır. fd değerleri, açık dosyaları veya soket bağlantılarını belirtir ve bu değerler üzerinden giriş/çıkış işlemleri gerçekleştirilir. open, read, write, close gibi sistem çağrıları, fd değerleri üzerinde çalışır. Standart giriş/çıkış tanımlayıcıları da fd’lerdir.


| 0 (stdin) | standart giriş (kullanıcıdan veri okumak için)
| 1 (stdout) | standart çıkış (veriyi ekrana yazdırmak için)
| 2 (stderr) | standart hata (hata mesajlarını ekrana yazdırmak için)


3 ve sonraki sayılar açık olan diğer dosyalar için atanır. Open – fopen eğer işlem başarısız olursa -1 değerini döndürür.


| İşlem                                     | Kod                                               |
|--------------------------------------------|---------------------------------------------------|
| Dosya açma ve dosya tanımlayıcısı alma     | `int fd = open("dosya.txt", O_RDONLY);`           |
| Dosyadan okuma                             | `char buffer[100]; read(fd, buffer, sizeof(buffer));` |
| Dosyayı kapatma                            | `close(fd);`                                       |


**FLAGS:**
	Dosya tanımlayıcıların belirli davranışlarını kontrol etmek ve yapılandırmak için kullanılır.

**O_RDONLY:**
Sadece okuma için dosya açma flag'ini temsil eder. Bu flag ile açılan dosya sadece okuma işlemleri için kullanılabilir. Dosya içeriği değiştirilemez.

**O_WRONLY:**
Sadece yazma için dosya açma flag'ini temsil eder. Bu flag ile açılan dosya sadece yazma işlemleri için kullanılabilir. Dosya içeriği okunamaz.

**O_RDWR:**
Hem okuma hem de yazma için dosya açma flag'ini temsil eder. Bu flag ile açılan dosya hem okuma hem de yazma işlemleri için kullanılabilir.

**O_CREAT:**
Eğer dosya yoksa, bu flag dosyayı oluşturur. Eğer dosya zaten varsa, bu flag'i kullanmak bir etki yapmaz.

**O_TRUNC:**
Dosya varsa içerisini temizler (sıfırlar). Dosyayı açarken içeriğini siler ve dosyayı sıfırdan başlatır (truncate).

**O_APPEND:**
Bu flag, dosyaya yazma işlemlerini her zaman dosyanın sonundan başlatır. Mevcut içeriği korur ve yeni veriyi dosyanın sonuna ekler.

**O_EXCL:**
Bu flag, dosya O_CREAT ile birlikte kullanıldığında, eğer dosya zaten varsa hata döndürür. Yani, dosya yaratılırken aynı isimde bir dosya zaten varsa hata verir.

Bu flag'ler, open sistem çağrısı veya benzeri işlemler sırasında kullanılır.
Örneğin:
int fd = open("dosya.txt", O_RDWR | O_CREAT, 0666);
Yukarıdaki örnekte, O_RDWR hem okuma hem yazma için, O_CREAT dosya oluşturmak için kullanılmıştır. 0666, dosyanın izinlerini temsil eder. (okuma izni=4, yazma izni=2, çalıştırma izni=1)
İlk rakam (06): Dosyanın sahibi (owner) için izinleri temsil eder.
İkinci rakam (6): Dosyanın sahibinin grubu (group) için izinleri temsil eder.
Üçüncü rakam (6): Diğer kullanıcılar (others) için izinleri temsil eder.

### **TYPECAST (TÜR DÖNÜŞÜMÜ)**
Typecast, bir veri türünü başka bir veri türüne dönüştürme işlemidir. Bu, genellikle iki farklı veri türü arasında bir uyumsuzluk olduğunda veya bir ifade içindeki veri türünü değiştirmek istediğinizde kullanılır.
double sayi = 3.14;
int tamsayi = (int)sayi; // Double'ı integer'a dönüştürür.

### **STATİK FONKSİYON**
Fonksiyon "static" olarak tanımlandığında, fonksiyonun sadece tanımlandığı dosya içinde (yani, yerel olarak) erişilebilir ve kullanılabilir olduğu anlamına gelir. Yani, fonksiyonun bağlı olduğu dosyanın dışında başka bir dosya tarafından erişilemeyeceği anlamına gelir. Bu, fonksiyonun dosya içinde yerel bir etki alanına sahip olduğu ve başka bir dosya tarafından tekrar tanımlanamadığı anlamına gelir.

### **CONST TÜRÜNDEKİ DEĞİŞKENLER**
C dilinde const anahtar kelimesi, programın çalışması boyunca değiştirilmeyecek değerleri tutan değişkenler için kullanılır. Bu tür değişkenlere sabitler denir. const ile tanımlanan bir değişken, bir kez değer atandıktan sonra program tarafından değiştirilemez. Örneğin, π (Pi) sayısı gibi sabit değerlerde kullanılır.

```c
#include <stdio.h>
int main() {
    const float PI = 3.14159; // PI = 5; Sabit değer (const) değiştirilemez. Hata verir
    printf("%f", PI);
    return 0;}
```

Bu program, PI sabitini ekrana yazdırır. PI’nın değeri bir kez atanır ve daha sonra değiştirilemez. Çıktı olarak 3.14159 görürsünüz. const anahtar kelimesi, sabitleri tanımlamak için kullanılırken, #define önişlemci bildirimi ile de sabitler tanımlanabilir. İşte bu iki yaklaşımın örnekleri:

**const ile sabit tanımlama:**

```c
#include <stdio.h>
void main() {
    const int SINIR = 500;
    const float PI = 3.141;
    printf("Sinir degeri: %d\n", SINIR);
    printf("Pi degeri: %f\n", PI);
    return 0;}
```

Çıktı:	Sinir degeri: 500

Pi degeri: 3.141000

**#define ile sabit tanımlama:**

```c
#include <stdio.h>
#define SINIR 500
#define PI 3.141
void main() {
    printf("Sinir degeri: %d\n", SINIR);
    printf("Pi degeri: %f\n", PI);
    return 0;}
```

Çıktı:	Sinir degeri: 500

Pi degeri: 3.141

Bu örneklerde, const ve #define ile sabit tanımlamalarını görebilirsiniz. const, daha güvenli ve veri tipine bağlı olarak sabitleri tanımlamak için tercih edilen bir yöntemdir. #define ise önişlemci direktifleri ile sabitleri tanımlar ve derleme öncesi değerleriyle kodun yerine geçer.

### **STRUCT VERİ YAPISI**
Struct (structure), C programlama dilinde farklı türdeki veri elemanlarını bir araya getirmek için kullanılan bir veri yapısıdır. struct ile, farklı veri türlerine sahip birden çok değişkeni tek bir veri yapısı içinde toplayabilirsiniz.

**STRUCT KULLANIMI:**
Struct ile oluşturulan veri yapısına, örnek bir değişken tanımlayarak erişilebilir.

```c
#include <stdio.h>
#include <string.h>
// Örnek bir struct tanımı
struct Ogrenci {
    char ad[50];
    int yas;
    float not_ortalamasi;
};
int main()
{
    struct Ogrenci ogrenci1;    // struct kullanımı
    strcpy(ogrenci1.ad, "Ahmet");    // Veri atama
    ogrenci1.yas = 20;
    ogrenci1.not_ortalamasi = 85.5;
    // Veriyi ekrana yazdırma
    printf("Ad: %s\n", ogrenci1.ad);
    printf("Yaş: %d\n", ogrenci1.yas);
    printf("Not Ortalaması: %.2f\n", ogrenci1.not_ortalamasi);
    return 0;
}
```

Bu örnekte, struct Ogrenci adında bir struct tanımlanmıştır. Bu struct'ın üç veri elemanı vardır: ad (bir karakter dizisi), yas (bir tamsayı) ve not_ortalamasi (bir ondalık sayı). struct kullanarak, bu farklı veri türlerini tek bir veri yapısı altında birleştirebiliyoruz.

**STRUCT ELEMANLARINA ERİŞİM:**
. (nokta) operatörü, struct elemanlarına erişmek için kullanılır.
ogrenci1.yas = 20;

**struct ile İşaretçi Kullanımı:**
-> (ok işareti) operatörü, struct türündeki bir işaretçinin elemanlarına erişmek için kullanılır.
struct Ogrenci* ogrenciPtr;
ogrenciPtr->yas = 20;

**Farklar:**
. operatörü doğrudan struct değişkenine, -> operatörü ise struct türündeki bir işaretçi üzerinden elemanlara erişir.
Örneğin, struct Ogrenci ogrenci1; için ogrenci1.yas kullanılırken, struct Ogrenci* ogrenciPtr; için ogrenciPtr->yas kullanılır.
Not:
Struct'lar, farklı veri türlerini bir araya getirerek daha organize ve yapılandırılmış veri yapıları oluşturmanıza olanak tanır. Örneğin, bir öğrenci bilgisi içeren bu struct, öğrenci listelerini, sınıf bilgilerini veya benzeri verileri daha organize bir şekilde temsil etmek için kullanılabilir.

### **BAĞLI LİSTE**
Bağlı liste, veri elemanlarının birbirine bağlı olduğu ve bir sonraki elemanın referansını içeren dinamik bir veri yapısıdır. Bu veri yapısı, bir diziye benzer, ancak elemanlar arasındaki bağlantılar dinamik olarak yönetilir.

**Bağlı Liste Elemanı (Node) Yapısı:**
Bağlı listenin temel yapı taşı, her elemanı temsil eden bir "node" veya düğüm yapısıdır. Bir node, iki ana bileşeni içerir:

**Veri Elemanı (Data):** Düğümün içinde saklanan asıl veri.

**Bağlantı (Next):** Bir sonraki düğüme işaret eden referans.

```c
struct Node
{
    int data;           // Elemanın verisini temsil eden öğe
    struct Node* next;  // Bir sonraki elemana işaret eden referans
};
```

**TYPEDEF:**
C programlama dilinde değişken tanımlarken kullanılan veri türlerini daha anlamlı kullanmak amacıyla veya kısa bir isimle kullanmak için kullanılır. Bu sayede kodlar daha okunaklı hale gelir, İşte bir örnek:

```c
typedef struct {
    char cdizi1[20];
    char cdizi2[20];
    int id;
} yap; // yap, struct yapısının kısa bir ismi

int main() {
    yap yd1, yd2;
    yd1.id = 1;
    yd2.id = 2;
    printf("yd1.id: %d, yd2.id: %d\n", yd1.id, yd2.id);
    return 0;
}
```

Bu örnekte, typedef ile struct içerisindeki bir yapıyı yap adı altında bir değişken türü olarak tanımladık.

## **FONKSİYONLAR-İŞLEVLERİ**

**memset:** Belirtilen bir bellek bloğunu belirli bir bayt değeri ile doldurur.

**bzero:** Bir bellek bloğunu sıfır değeri ile sıfırlar.

**memcpy:** Bir bellek bloğunu başka bir bellek bloğuna kopyalar.

**memmove:**Bir bellek bloğunu başka bir bellek bloğuna güvenli bir şekilde kopyalar.(ovarlap durumunda bile doğru kopyalamak için bellek bloklarının adreslerine göre kopyalama işlemi yapar.)

**memchr:** Bir bellek bloğu içinde belirli bir baytı arar ve bulduğu ilk konumun adresini döndürür.

**memcmp:** İki bellek bloğunu karşılaştırır farklı bir karakter bulduğunda farklarını döndürür.

**strlen:** Bir dizinin uzunluğunu bulur.

**strdup:** Verilen bir dizinin bir kopyasını bellekte açtığı yere kopyalar ve bu bellek adresini döndürür.

**strlcpy:** Bir diziyi başka bir diziye boyutu kontrol edilerek kopyalar. Taşma durumu önlenir. Return değeri hedef dizinin boyutunu döndürür.

**strlcat:** Bir karakter dizisinin sonuna başka bir karakter dizisini eklemek için kullanılır. Dizinin boyutlarına göre işlem yapar.

**strchr:** Bir karakter dizisi içerisinde aranan karakteri ilk bulduğu konumu döndürür.

**strrchr:** Bir karakter dizisinde sondan başlayarak karakteri arar ve bulduğu konumu döndürür.

**strnstr:** Bir dizide belirli bir uzunluktaki bir alt diziyi arar ve bulduğu ilk konumu döndürür. Bulamazsa NULL döndürür.

**strncmp:** İki diziyi belirli bir uzunluğa kadar karşılaştırır. Fark varsa bulduğu farkı döndürür.

**atoi:** ASCII karakterlerini içeren bir diziyi tamsayıya dönüştürür.

**itoa:** Tam sayıyı ascii karaktere dönüştürür.

**calloc:** Bellek tahsisi yapar ve bellek alanını sıfırlar.

**isalpha:** Bir karakterin alfabede yer alıp almadığını kontrol eder.

**isdigit:** Bir karakterin rakam olup olmadığını kontrol eder.

**isalnum:** Bir karakterin alfanumerik (harf ya da rakam) olup olmadığını kontrol eder.

**isascii:** Bir karakterin ASCII karakteri olup olmadığını kontrol eder.

**isprint:** Bir karakterin yazdırılabilir bir karakter olup olmadığını kontrol eder (boşluk karakteri dahil).

**toupper:** Küçük harfi büyük harfe dönüştürür.

**tolower:** Büyük harfi küçük harfe dönüştürür.
 
