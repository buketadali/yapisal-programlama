#include <stdio.h>
#include <stdlib.h>

#include <string.h>
//Buket ADALI 170401014
//Yapisal programlama vize odevi 2020
//kart oyunu

struct KART {
    char *cins;
    char *no;
};

int main(void){
    enbas:
    printf("\n------------------------------------\n" );
    printf("\nKART OYUNU\n\n");
    printf("------------------------------------\n" );

    int i;
    struct KART Deste[52];
    char *no[]={"As", "Papaz", "Kiz", "Vale", "On", "Iki", "Uc", "Dort", "Bes", "Alti", "Yedi", "Sekiz", "Dokuz"};
    char *cins[]={"Kupa", "Karo", "Maca", "Sinek"};
    desteYap(Deste,cins,no);


    karistir(Deste);
    dagit(Deste);


    printf("\n10. el sonu ve oyun bitmistir.\n");

     sor:
        printf("\nBu oyuna devam etmek isterseniz klavyenizden 'd' bu oyunu bitirip cikmak isterseniz  'c' girin : \n");

        char buffer[1];
        scanf("%s" , buffer) ;

        if (strcmp ("d",buffer) == 0){
            printf(" oyuna bastan baslaniyor...");
            printf("kartlar karistirilip yeni sekilde dagitiliyor..");
            goto enbas;
        }
        else{
            if (strcmp ("c",buffer) == 0){
                printf("oyundan cikiliyor...");


            }
            else{
                printf("gecersiz bir harf girdiniz! tekrar deneyin.");
                goto sor;
            }
        }


    printf("\n");
    printf("------------------------------------\n" );



    return 0;
}

void desteYap(struct KART *Deste, char *cins[], char *no[]){
    int i;
    for(i = 0 ; i<52 ; i++){
        Deste[i].no=no[i%13];
        Deste[i].cins=cins[i/13];
    }
}


int kazananiBul(struct KART *el){

                //primer kazanma kriteri >> Kupa>Karo>Maça>Sinek
            //sekonder kazanma kriteri >> As>Papaz>Kız>Vale>...
    int i;
    int adaypuani[] = {0,0,0,0};

    //bu program puanlandirma yoluyla kazanana karar verecek.

    for( i = 0 ; i < 4 ; ++i ){
        //adayin elindeki kartın cinsine göre ciddi bir gruplama yapmamız gerek.
        //cinsi üstün olan bir kart, numarası üstün olan bir kart tarafından egale edilmemeli.
        //bunun için, oyuncuların elindeki kartın cinsine bakılarak çok büyük aralıklı sayılar eklenir.

        if (strcmp((el[i+1].cins),"Kupa" ) == 0 )
        {
            adaypuani[i] = adaypuani[i] + 10000 ;
        }

        if (strcmp((el[i+1].cins),"Karo" ) == 0 )
        {
            adaypuani[i] = adaypuani[i] + 1000 ;
        }

        if (strcmp((el[i+1].cins),"Maca" ) == 0 )
        {
            adaypuani[i] = adaypuani[i] + 100 ;
        }

        //adayin elindeki kartın numarasına göre ikincil bir gruplama yapmamız gerek.
        //bu aşamada, cinsi üstün olan kartlar arasında bir mücadele söz konusu...
        //bunun için, oyuncuların elindeki kartın numarası kadar puan eklemek yeterli olacak.

        if (strcmp((el[i+1].no),"Iki" ) == 0 )
        {
            adaypuani[i] = adaypuani[i] + 2 ;
        }

        if (strcmp((el[i+1].no),"Uc" ) == 0 )
        {
            adaypuani[i] = adaypuani[i] + 3 ;
        }

        if (strcmp((el[i+1].no),"Dort" ) == 0 )
        {
            adaypuani[i] = adaypuani[i] + 4 ;
        }

        if (strcmp((el[i+1].no),"Bes" ) == 0 )
        {
            adaypuani[i] = adaypuani[i] + 5 ;
        }

        if (strcmp((el[i+1].no),"Alti" ) == 0 )
        {
            adaypuani[i] = adaypuani[i] + 6 ;
        }

        if (strcmp((el[i+1].no),"Yedi" ) == 0 )
        {
            adaypuani[i] = adaypuani[i] + 7 ;
        }

        if (strcmp((el[i+1].no),"Sekiz" ) == 0 )
        {
            adaypuani[i] = adaypuani[i] + 8 ;
        }

        if (strcmp((el[i+1].no),"Dokuz" ) == 0 )
        {
            adaypuani[i] = adaypuani[i] + 9 ;
        }

        if (strcmp((el[i+1].no),"On" ) == 0 )
        {
            adaypuani[i] = adaypuani[i] + 10 ;
        }

        if (strcmp((el[i+1].no),"Vale" ) == 0 )
        {
            adaypuani[i] = adaypuani[i] + 11 ;
        }

        if (strcmp((el[i+1].no),"Kiz" ) == 0 )
        {
            adaypuani[i] = adaypuani[i] + 12 ;
        }

        if (strcmp((el[i+1].no),"Papaz" ) == 0 )
        {
            adaypuani[i] = adaypuani[i] + 13 ;
        }

        if (strcmp((el[i+1].no),"As" ) == 0 )
        {
            adaypuani[i] = adaypuani[i] + 14 ;
        }

    }

    //adaypuani dizisinde her oyuncunun elindeki kartın değeri tutuluyor.
    //puanlar karşılaştırılarak, en büyük puanlı oyuncu kazanan ilan edilecek.

    //kazanan değişkeni kazanan oyuncunun indeksini tutar.
    int kazanan = 0;
    int say;
        for (say = 1; say < 4; say++)
        {
            if (adaypuani[kazanan] < adaypuani[say])
            kazanan = say;
        }
    printf("Kazanan : %d. oyuncu \n" , kazanan+1);
    return kazanan+1;


}


void dagit(struct KART *Deste){
    int genelPuan[]={0,0,0,0};
    int oyuncu = 1;
    struct KART el[5];
    int i;
    for (i = 0 ; i<40 ; ++i){

        printf("%d . oyuncu : %s %s kartini cekti \n", oyuncu  , Deste[i].cins , Deste[i].no);

        el[oyuncu].cins = Deste[i].cins;
        el[oyuncu].no = Deste[i].no;

        //printf("%s %s",el[oyuncu].cins,el[oyuncu].no);

        oyuncu ++ ;
        if( (i+1) % 4 == 0)
        {
            printf("\n%d . El Bitti...\n", (i+1)/4  );

            int kazanan=kazananiBul(el);
            genelPuan[kazanan-1]=genelPuan[kazanan-1]+1;
            int c;
            for(c=0; c<4; ++c){
                    printf("%d. oyuncunun genel puani : %d\n",c+1,genelPuan[c]);

            }


            printf("------------------------------------" );
            printf("\n");
            oyuncu = 1 ;
        }
    }

}

void karistir(struct KART *Deste){
    int i,j;
    struct KART temp;
    for(i = 0 ; i<52 ; i++){
        j=rand()%52;
        temp=Deste[i];
        Deste[i]=Deste[j];
        Deste[j]=temp;
    }
}

