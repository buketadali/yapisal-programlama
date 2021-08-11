#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//Buket ADALI 170401014
//yapýsal final 2020
//piþti oyunu

#define True 1
#define False 0

struct Kart{
    int kartTip;
    int kartNo;
    int tutucu;
};

struct Deste{
    struct Kart Kartlar[52];
};

struct Duzenleyici{
    struct Deste Deste;
    struct Deste karismisDeste;

    int desteÝlki;

    int kalanSayisi;
    int* yerdekiKart;
    int kalanYer;

    int oyuncuKartSayisi;
    int* oyuncuEldekiKartlari;
    int oyuncuToplam;
    int* oyuncuToplamKart;
    int oyuncuPistiSayisi;
    int oyuncuValePistiSayisi;

    int pcKartSayisi;
    int* pcKartlari;
    int pcToplam;
    int* pcToplamKart;
    int pcPistiSayisi;
    int pcValePistiSayisi;

    int oyuncuAttigi[52];
    int oyuncuHamlesi;

    int pcAttigi[52];
    int pcHamle;

    int elSayisi;
    int bitis;

};

void oyunuBaslat(struct Duzenleyici* );
void desteYaz(struct Deste , int , int );
void desteKaristir(struct Deste* , int , int );
int desteÝlkiBul(struct Deste , int );
void kartEliDegis(struct Duzenleyici* , int , int );
void yenile(struct Duzenleyici* );
void printDuzenleyici(struct Duzenleyici );
void oyuncuBekle(struct Duzenleyici* );
void ekraniyazdir(struct Koordinator* );
void hamleBaslat(struct Duzenleyici* , int , int, int );
void pcHamleYap(struct Duzenleyici* );
int kartIndexiBul(struct Duzenleyici , int , int );
void elBitisi(struct Duzenleyici* );
char* kartTipi(int );
void oyunSonlandý(struct Duzenleyici* );

int main()
{
    struct Duzenleyici duzenleyen;
    oyunuBaslat(&duzenleyen);

    while (1)
    {
        ekraniyazdir(&duzenleyen);
        oyuncuBekle(&duzenleyen);
        pcHamleYap(&duzenleyen);
        elBitisi(&duzenleyen);

        if (duzenleyen.son == 1)
            break;
    }
    oyunSonlandý(&duzenleyen);
    return 0;
}

void oyunuBaslat(struct Duzenleyici* duzenleyen)
{
    int i=0;
    int tip=0, numara=0;
    struct Kart sanal;
    struct Deste ilk;
    for(i=0; i<4*13; i++)
    {
        sanal.kartNo = numara;
        sanal.kartTip = tip;
        sanal.tutucu = 0;
        ilk.Kartlar[i] = sanal;
        numara++;
        if (numara%13 == 0){
            numara = 0;
            tip++;
        }
        duzenleyen->pcAttigi[i] = 0;
        duzenleyen->oyuncuAttigi[i] = 0;

    }
    duzenleyen->Deste = ilk;
    duzenleyen->karismisDeste = ilk;
    duzenleyen->desteÝlki = 0;
    duzenleyen->bitis = 0;

    duzenleyen->pcHamle = 0;
    duzenleyen->oyuncuHamle = 0;
    duzenleyen->oyuncuPistiSayisi  = 0;
    duzenleyen->pcPistiSayisi  = 0;
    duzenleyen->oyuncuValePistiSayisi = 0;
    duzenleyen->pcValePistiSayisi = 0;


    desteKaristir(&duzenleyen->karismisDeste, 4, 13);
    kartEliDegis(duzenleyen, 0, 10);
    kartEliDegis(duzenleyen, 1, 10);
    kartEliDegis(duzenleyen, 2, 10);
    kartEliDegis(duzenleyen, 3, 10);
    kartEliDegisDegist(duzenleyen, 4, 20);
    kartEliDegisDegist(duzenleyen, 5, 20);
    kartEliDegis(duzenleyen, 6, 20);
    kartEliDegis(duzenleyen, 7, 20);
    duzenleyen->desteÝlki += 8;
    kartEliDegistir(duzenleyen, 8, 30);
    kartEliDegis(duzenleyen, 9, 30);
    kartEliDegistir(duzenleyen, 10, 30);
    kartEliDegistir(duzenleyen, 11, 30);
    duzenleyen->pcToplam = 0;
    duzenleyen->oyuncuToplam = 0;
    duzenleyen->desteÝlki += 4;
    yenile(duzenleyen);
    duzenleyen->kalanYeryer = 11;
    duzenleyenr->elSayisi = 1;
}

void oyunBitisi(struct Duzenleyici* duzenleyen)
{
    int oyuncuPuan = 0;
    int pcPuan = 0;

    oyuncuPuan += duzenleyen->oyuncuPistiSayisi*10;
    oyuncuPuan += duzenleyen->oyuncuValePistiSayisi*20;
    pcPuan += duzenleyen->pcPistiSayisi*10;
    pcPuan += duzenleyen->pcValePistiSayisi*20;

    int i=0;
    for(i=0; i<duzenleyen->pcToplam; i++)
    {
        if (duzenleyen->karismisDeste.Kartlar[duzenleyen->pcToplamKart[i]].kartNo == 1)
        {
            pcPuan += 1;
        }

        if (duzenleyen->karismisDeste.Kartlar[duzenleyen->pcToplamKart[i]].kartNo == 11)
        {
            pcPuan += 1;
        }

        if ( duzenleyen->karismisDeste.Kartlar[duzenleyen->pcToplamKart[i]].kartTip == 2 &&
                duzenleyen->karismisDeste.Kartlar[duzenleyen->pcToplamKart[i]].kartNo == 10)
        {
            pcPuan += 3;
        }

        if ( duzenleyen->karismisDeste.artlar[duzenleyen->pcToplamKart[i]].kartTip == 1 &&
                duzenleyen->karismisDeste.Kartlar[duzenleyen->pcToplamKart[i]].kartNo == 2)
        {
            pcPuan += 2;
        }
    }

    for(i=0; i<duzenleyen->oyuncuToplam; i++)
    {
        if (duzenleyen->karismisDeste.Kartlar[duzenleyen->oyuncuToplamKart[i]].kartNo == 1)
        {
            pcPuan += 1;
        }

        if (duzenleyen->karismisDeste.Kartlar[duzenleyen->oyuncuToplamKart[i]].kartNo == 11)
        {
            pcPuan += 1;
        }

        if ( duzenleyen->karismisDeste.Kartlar[duzenleyen->oyuncuToplamKart[i]].kartTip == 2 &&
                duzenleyen->karismisDeste.Kartlar[koordinator->oyuncuToplamKart[i]].kartNo == 10)
        {
            pcPuan += 3;
        }

        if ( duzenleyen->karismisDeste.Kartlar[duzenleyenr->oyuncuToplamKart[i]].kartTip == 1 &&
                duzenleyen->karismisDeste.Kartlar[duzenleyen->oyuncuToplamKart[i]].kartNo == 2)
        {
            pcPuan += 2;
        }
    }

    if (duzenleyen->pcToplam > duzenleyen->oyuncuToplam)
    {
        pcPuan += 3;
    }
    if (duzenleyen->oyuncuToplam > duzenleyen->pcToplam)
    {
        oyuncuPuan += 3;
    }

    printf("#--------------------------------------------------------------------------------#\n");
    printf("|                          - Oyun Bitmistir...                                 |\n");
    printf("#--------------------------------------------------------------------------------#\n");
    printf("Bilgisayarin Puani: %d\n", cpuPuan);
    printf("Oyuncunun Puani %d\n", oyuncuPuan);

    if (pcPuan > oyuncuPuan)
    {
        printf("Bilgisayar Kazandi!");
    }
    if (pcPuan < oyuncuPuan)
    {
        printf("Oyuncu  Kazandi!");
    }
    if (pcPuan == oyuncuPuan)
    {
        printf("Berabere!");
    }
}

void desteyiKaristir(struct Deste* deste, int tip, int numara)
{
    int i=0;
    struct Kart temp;
    int random=0;
    srand(time(NULL));
    for(i=0; i<tip*numara; i++)
    {
        random = rand()%(tip*numara);
        temp = deste->Kartlar[i];
        deste->Kartlar[i] = deste->Kartlar[random];
        deste->Kartlar[random] = temp;
    }
}

void desteyiYazdir(struct Deste deste, int tip, int numara)
{
    int i=0;
    for(i=0; i<tip*numara; i++)
    {
        printf("%d, %d - %d - %d\n", i, deste.Kartlar[i].kartTip,
               deste.Kartlar[i].kartNo, deste.Kartlar[i].tutucu);
    }
}

int desteÝlkiBul(struct Deste deste, int tane)
{
    int i=0;
    for(i=0; i<tane; i++)
    {
        if (deste.Kartlar[i].tutucu == 0)
            return i;
    }
    return i;
}

void kartEliDegis(struct Duzenleyici* duzenleyen, int index, int hangi)
{
    duzenleyen->karismisDeste.Kartlar[index].tutucu = hangi;
}

void yenile(struct Duzenleyici* duzenleyen)
{
    int i=0, kalan = 0;
    int pc=0, oyuncu=0;
    int pcToplam = 0, oyuncuToplam = 0;
    for(i=0; i<52; i++)
    {
        if (duzenleyen->karismisDeste.Kartlar[i].tutucu == 30)
        {
            kalan++;
        }
        if (duzenleyen->karismisDeste.Kartlar[i].tutucu == 10)
        {
            pc++;
        }
        if (duzenleyen->karismisDeste.Kartlar[i].tutucu == 15)
        {
            pcToplam++;
        }
        if (duzenleyen->karismisDeste.Kartlar[i].tutucu == 20)
        {
            oyuncu++;
        }
        if (duzenleyen->karismisDeste.Kartlar[i].tutucu == 25)
        {
            oyuncuToplam++;
        }
    }

    int* kalanKart = (int*)malloc(sizeof (int)*kalan);
    int* pcKart = (int*)malloc(sizeof (int)*pc);
    int* oyuncuKart = (int*)malloc(sizeof (int)*oyuncu);
    int* pcToplamKart = (int*)malloc(sizeof (int)*pcToplam);
    int* oyuncuToplamKart = (int*)malloc(sizeof (int)*oyuncuToplam);

    int y=0, c=0, o=0;
    int p=0, v=0;
    for(i=0; i<52; i++)
    {
        if (duzenleyen->karismisDeste.artlar[i].tutucu == 30)
        {
            kalanKart[y] = i;
            y++;
        }
        if (duzenleyen->karismisDeste.Kartlar[i].tutucu == 10)
        {
            pcKart[c] = i;
            c++;
        }
        if (duzenleyen->karismisDeste.Kartlar[i].tutucu== 15)
        {
            pcKart[v] = i;
            v++;
        }
        if (duzenleyen->karismisDeste.Kartlar[i].tutucu== 20)
        {
            oyuncuKart[o] = i;
            o++;
        }
        if (duzenleyen->karismisDeste.Kartlar[i].tutucu == 25)
        {
            oyuncuToplamKart[p] = i;
            p++;
        }
    }

    duzenleyen->kalanKartlar = kalanKart;
    duzenleyen->kalanSayisi = kalan;
    duzenleyen->pcKartlari = pcKart;
    duzenleyen->pcKartSayisi = pc;
    duzenleyen->oyuncuKartlari = oyuncuKart;
    duzenleyen->oyuncuKartSayisi = oyuncu;
    duzenleyen->pcToplamKart = cpuToplamKart;
    duzenleyen->oyuncuToplamKart = oyuncuToplamKart;
    duzenleyen->oyuncuToplam = oyuncuToplam;
    duzenleyen->pcToplam = pcToplam;
}

void printDuzenleyici(struct Duzenleyici duzenleyen)
{
    int i = 0;
    for(i=0; i<duzenleyen.kalanSayisi; i++)
    {
        printf("%d\n", duzenleyen.kalanKartlar[i]);
    }
    for(i=0; i<duzenleyen.pcKartSayisi; i++)
    {
        printf("%d\n", duzenleyen.pcKartlari[i]);
    }
    for(i=0; i<duzenleyen.oyuncuKartSayisi; i++)
    {
        printf("%d\n", duzenleyen.oyuncuKartlari[i]);
    }

}

void oyuncuBekle(struct Duzenleyici* duzenleyen)
{
    int numara=0, karttip;
    int boz = 0;
    while (boz == 0)
    {
        printf("\n");
        printf("Tip -> 0: Kupa, 1:Maca, 2:Karo, 3:Sinek\n");
        printf("Numara -> 1: A...... 11:J, 12:Q, 13:K\n");
        printf("Ornek: Karo 7 = 3 7\n");
        printf("Girdi Bekleniyor: ");
        scanf("%d %d", &karttip, &numara);

        int i=0;
        int bulunan = 0;
        for(i=0; i<duzenleyen->oyuncuKartSayisi; i++)
        {
            if (duzenleyen->oyuncuKartlari[i] == kartIndexiBul(*duzenleyen, karttip, numara))
            {
                bulunan = 1;
                boz = 1;
                break;
            }
        }
        if (bulundu == 0)
        {
            printf("Kullanici %s-%d kartina sahip degil. Tekrar deneyiniz.", kartTipi(karttip), numara);
        }
    }
    printf("\n\n");
    hamleBaslat(duzenleyen, 20, karttip, numara);

}

void ekraniBaslat(struct Duzenleyici* duzenleyen)
{
    int i=0;
    printf("#--------------------------------------------------------------------------------#\n");
    printf("|             Pisti Oyunu - El %d.\n", duzenleyen->elSayisi);
    printf("#--------------------------------------------------------------------------------#\n");
    printf("|                  string karakterler girmeyiniz!                    |\n");
    printf("#--------------------------------------------------------------------------------#\n");
    printf("|                  0-> KUPA   1-> MACA    2->KARO    3->SINEK                     |\n");
    printf("#--------------------------------------------------------------------------------#\n");
    printf("|                  Ornek Input: Karo-7 = 3 7,  Kupa-2 = 0 2                       |\n");
    printf("#--------------------------------------------------------------------------------#\n");


    printf("| Yerde Toplanan      | ");
    for(i=0; i<duzenleyen->kalanSayisi; i++)
    {
        int tip = duzenleyen->karismisDeste.Kartlar[duzenleyen->kalanKartlar[i]].kartTip;
        int no = duzenleyen->karismisDeste.Kartlar[duzenleyen->kalanKartlar[i]].kartNo;
        printf("%s-%d, ", kartTipi(tip), no);
        if (duzenleyen->kalanSayisi%8 == 0 && i!=0)
        {
            printf("\n|                     |");
        }
    }
    printf("\n|                     |");
    printf("\n#--------------------------------------------------------------------------------#\n");
    printf("| kalan Son         | ");
    if (duzenleyen->kalanSayisi > 0)
    {
        int tip = duzenleyen->karismisDeste.Kartlar[duzenleyen->kalanYer].kartTip;
        int no = duzenleyen->karismisDeste.Kartlar[duzenleyen->kalanyer].kartNo;
        printf("%s-%d, ", kartTipi(tip), no);

    }
    printf("\n");
    printf("|                     |\n");
    printf("#--------------------------------------------------------------------------------#\n");
    printf("| Oyuncunun Elindekiler    | ");
    for(i=0; i<duzenleyen->oyuncuKartSayisi; i++)
    {
        int tip = duzenleyen->karismisDeste.Kartlar[duzenleyen->oyuncuKartlari[i]].kartTip;
        int no = duzenleyen->karismisDeste.Kartlar[duzenleyen->oyuncuKartlari[i]].kartNo;
        printf("%s-%d, ", kartTipi(tip), no);
    }
    printf("\n|                     |");
    printf("\n");
    printf("#--------------------------------------------------------------------------------#\n");
    printf("| pc attigi          | ");
    for(i=0; i<duzenleyen->pcHamle; i++)
    {
        int tip = duzenleyen->karismisDeste.Kartlar[duzenleyen->pcAttigi[i]].kartTip;
        int no =  duzenleyen->karismisDeste.Kartlar[duzenleyen->pcAttigi[i]].kartNo;
        printf("%s-%d, ", kartTipi(tip), no);
    }
    printf("\n|                     |");
    printf("\n");
    printf("#--------------------------------------------------------------------------------#\n");
    printf("| Oyuncunun attigi    | ");
    for(i=0; i<duzenleyen->oyuncuHamle; i++)
    {
        int tip = duzenleyen->karismisDeste.Kartlar[duzenleyen->oyuncununAttigi[i]].kartTip;
        int no = duzenleyen->karismisDeste.Kartlar[duzenleyen->oyuncununAttigi[i]].kartNo;
        printf("%s-%d, ", kartTipi(tip), no);
    }
    printf("\n|                     |");
    printf("\n");
    printf("#--------------------------------------------------------------------------------#\n");


    printf("Oyuncunun topladigi toplam kart: %d\n", duzenleyen->oyuncuToplam);
    printf("Bilgisayarin topladigi toplam kart: %d\n", duzenleyen->cpuToplam);
}

void hamleBaþlat(struct Duzenleyici* duzenleyen, int hangi, int tip, int numara)
{
    int i=0;
    if (duzenleyen->karismisDeste.Kartlar[duzenleyen->kalanYeryer].kartNo == numara)
    {
        if (duzenleyen->kalanSayisi == 1 && hangi == 20)
        {
            printf("Tebrikler Pisti oldu!\n");
            duzenleyen->oyuncuPistiSayisi += 1;
        }
        if (duzenleyen->kalanSayisi == 1 && kim ==10)
        {
            printf("Bilgisayar pisti yapti!\n");
            duzenleyen->pcPistiSayisi += 1;
        }
        if (hangi == 20)
            printf("Tebrikler yerdeki kartlari topladýnýz!\n");
        if (hangi == 10)
            printf("Bilgisayar yerdeki kartlari topladý!\n");
        for(i=0; i<duzenleyen->kalanSayisi; i++)
        {
            duzenleyen->karismisDeste.Kartlar[duzenleyen->kalanKartlar[i]].tutucu = hangi+5;
        }
        duzenleyen->karismisDeste.Kartlar[kartIndexiBul(*duzenleyen, tip, numara)].tutucu = hangi + 5;
        duzenleyen->kalanSayisi = 0;
        duzenleyen->kalanyer = -1;
    }
    else if (numara == 11)
    {
        if (duzenleyen->kalanSayisi == 1 && hangi == 20)
        {
            printf("Tebrikler Vale ile Pisti Yaptiniz!\n");
            duzenleyen->oyuncuValePistiSayisi += 1;
        }
        if (duzenleyen->kalanSayisi == 1 && kim ==10)
        {
            duzenleyen->pcValePistiSayisi += 1;
            printf("Bilgisayar Vale ile pisti yapti!\n");
        }
        if (hangi == 20)
            printf("Vale ile yerdeki kartlari aldiniz!\n");
        if (hangi == 10)
            printf("Bilgisayar Vale ile yerdeki kartlari aldi!\n");
        for(i=0; i<duzenleyen->kalanSayisi; i++)
        {
            duzenleyen->karismisDeste.Kartlar[duzenleyen->kalanKartlar[i]].tutucu = hangi+5;
        }
        duzenleyen->karismisDeste.Kartlar[kartIndexiBul(*duzenleyen, tip, numara)].tutucu = hangi + 5;
        duzenleyen->kalanSayisi = 0;
        duzenleyen->kalanyer = -1;
    }
    else {
        duzenleyen->karismisDeste.Kartlar[kartIndexiBul(*duzenleyen, tip, numara)].tutucu = 30;
        duzenleyen->kalanSayisi++;
        duzenleyen->kalanyer = kartIndexiBul(*duzenleyen, tip, numara);
    }

    if (hangi==10)
    {
        duzenleyen->pcAttigi[duzenleyen->pcHamle] = kartIndexiBul(*duzenleyen, tip, numara);
        duzenleyen->pcHamle++;
    }
    if (hangi==20)
    {
        duzenleyen->oyuncununAttigi[duzenleyen->oyuncununHamle] = kartIndexiBul(*duzenleyen, tip, numara);
        duzenleyen->oyuncununHamle++;
    }
    yenile(duzenleyen);
}

int kartIndexiBul(struct Duzenleyici duzenleyen, int tip, int numara)
{
    int i = 0;
    for(i=0; i<52;i++)
    {
        if (duzenleyen.karismisDeste.Kartlar[i].kartNo == numara &&
                duzenleyen.karismisDeste.Kartlar[i].kartTip == tip)
            return i;
    }
    return i;
}

void bilgisayarHamleYap(struct Koordinator* koordinator)
{
    int i=0;
    int tur = 0;
    for(i=0; i<koordinator->pcKartSayisi; i++)
    {
        if (koordinator->karismisDeste.Kartlar[koordinator->pcKartlari[i]].kartNo == 11)
        {
            hamleBaslat(koordinator, 10,
                               koordinator->karismisDeste.Kartlar[koordinator->pcKartlari[i]].kartTip,
                    koordinator->karismisDeste.Kartlar[koordinator->pcKartlari[i]].kartNo);
            tur = 1;
            return;
        }
        else if (koordinator->karismisDeste.Kartlar[koordinator->pcKartlari[i]].kartNo == koordinator->karismisDeste.Kartlar[koordinator->sonyer].kartNo)
        {
            hamleBaslat(koordinator, 10,
                               koordinator->karismisDeste.Kartlar[koordinator->pcKartlari[i]].kartTip,
                    koordinator->karismisDeste.Kartlar[koordinator->pcKartlari[i]].kartNo);
            tur = 1;
            return;
        }
        else
        {
            tur = tur*1;
        }
    }
    if (tur==0)
    {
        hamleBaslat(koordinator, 10,
                           koordinator->karismisDeste.Kartlar[koordinator->pcKartlari[0]].kartTip,
                koordinator->karismisDeste.Kartlar[koordinator->pcKartlari[0]].kartNo);
        return;
    }
}

void elBitisi(struct Koordinator* koordinator)
{
    if (koordinator->pcKartSayisi == 0)
    {
        koordinator->elSayisi+=1;
        kartEliDegis(koordinator, koordinator->desteÝlki, 10);
        kartEliDegis(koordinator, koordinator->desteÝlki+1, 10);
        kartEliDegis(koordinator, koordinator->desteÝlki+2, 10);
        kartEliDegis(koordinator, koordinator->desteÝlki+3, 10);
        kartEliDegis(koordinator, koordinator->desteÝlki+4, 20);
        kartEliDegis(koordinator, koordinator->desteÝlki+5, 20);
        kartEliDegiskoordinator, koordinator->desteÝlki+6, 20);
        kartEliDegis(koordinator, koordinator->desteÝlki+7, 20);
        koordinator->desteÝlki += 8;
        kartEliDegis(koordinator, koordinator->desteÝlki+8, 30);
        kartEliDegis(koordinator, koordinator->desteÝlki+9, 30);
        kartEliDegis(koordinator, koordinator->desteÝlki+10, 30);
        kartEliDegis(koordinator, koordinator->desteÝlki+11, 30);
        koordinator->destÝlki += 4;
        koordinator->kalanyer = koordinator->desteÝlki-1;
        koordinator->pcHamle = 0;
        koordinator->oyuncuHamle = 0;
        yenile(koordinator);
    }

    if (koordinator->desteÝlki >= 49 )
    {
        koordinator->bitis = 1;
    }
}

char* kartTipi(int tip)
{
    char* text = NULL;
    if (tip == 0)
    {
        text = "Kupa";
    }
    if (tip == 1)
    {
        text = "Maca";
    }
    if (tip == 2)
    {
        text = "Karo";
    }
    if (tip == 3)
    {
        text = "Sinek";
    }
    return text;
}
