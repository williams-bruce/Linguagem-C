#include <stdio.h>
#define True 1
#define False 0

char pelotao();
void getNotas(float notas[]);
float media(float notas[]);

int main(){

    int vencedor = 0;
    float maior_media = 0;
    //  vetor de notas de cada pelotão
    float notas1[5];
    float notas2[5];
    float notas3[5];
    float notas4[5];

    //  verificador de pelotao repetido
    int repetido1 = False;
    int repetido2 = False;
    int repetido3 = False;
    int repetido4 = False;

    //  verifica se todos todos os pelotoes ja foram avaliados
    int tudo_ok = 0;

    while(tudo_ok != 4){
        switch (pelotao()){
            case '1':{
                if (repetido1){
                    puts("NUMERO DE PELOTAO REPETIDO!");
                    break;
                }
                getNotas(notas1);
                printf("Pelotao 1 Media %.1f\n\n", media(notas1));
                if (media(notas1) > maior_media){
                    vencedor = 1;
                    maior_media = media(notas1);
                }
                repetido1 = True;
                tudo_ok++;
                break;
            }
            case '2':{
                if (repetido2){
                    puts("NUMERO DE PELOTAO REPETIDO!");
                    break;
                }
                getNotas(notas2);
                printf("Pelotao 2 Media %.1f\n\n", media(notas2));
                if (media(notas2) > maior_media){
                    vencedor = 2;
                    maior_media = media(notas2);
                }
                repetido2 = True;
                tudo_ok++;
                break;
            }
            case '3':{
                if (repetido3){
                    puts("NUMERO DE PELOTAO REPETIDO!");
                    break;
                }
                getNotas(notas3);
                printf("Pelotao 3 Media %.1f\n\n", media(notas3));
                if (media(notas3) > maior_media){
                    vencedor = 3;
                    maior_media = media(notas3);
                }
                repetido3 = True;
                tudo_ok++;
                break;
            }
            case '4':{
                if (repetido4){
                    puts("NUMERO DE PELOTAO REPETIDO!");
                    break;
                }
                getNotas(notas4);
                printf("Pelotao 4 Media %.1f\n\n", media(notas4));
                if (media(notas4) > maior_media){
                    vencedor = 4;
                    maior_media = media(notas4);
                }
                repetido4 = True;
                tudo_ok++;
                break;
            }
            default:{
                puts("NUMERO DE PELOTAO INVALIDO!");
                break;
            }
        }
    }
    
    puts("\n\n");

    puts("RESULTADO FINAL");
    puts("===============\n");

    printf("Pelotao 1 Media %.1f\n", media(notas1));
    printf("Pelotao 2 Media %.1f\n", media(notas2));
    printf("Pelotao 3 Media %.1f\n", media(notas3));
    printf("Pelotao 4 Media %.1f\n", media(notas4));

    printf("Vencedor Pelotao %d Nota %1.f", vencedor, maior_media);

    return 0;
}

char pelotao(){
    puts("Digite o nr do pelotao(1/2/3/4):");
    char pelotao;
    scanf(" %c", &pelotao);
    fflush(stdin);
    return pelotao;
}

void getNotas(float notas[]){
    puts("Digite as notas das categorias:");
    float aux;

    while(1){
        aux = -1;
        printf("Alinhamento e cobertura: ");
        scanf(" %f", &aux);
        if (aux < 0.0 || aux > 10.0){
            puts("NOTA INVALIDA! DIGITE NOVAMENTE.");
            continue;
        }
        notas[0] = aux;
        break;
    }

    while(1){
        aux = -1;
        printf("Apresentacao individual: ");
        scanf(" %f", &aux);
        if (aux < 0.0 || aux > 10.0){
            puts("NOTA INVALIDA! DIGITE NOVAMENTE.");
            continue;
        }
        notas[1] = aux;
        break;
    }

    while(1){
        aux = -1;
        printf("Movimentos com arma: ");
        scanf(" %f", &aux);
        if (aux < 0.0 || aux > 10.0){
            puts("NOTA INVALIDA! DIGITE NOVAMENTE.");
            continue;
        }
        notas[2] = aux;
        break;
    }

    while(1){
        aux = -1;
        printf("vibracao: ");
        scanf(" %f", &aux);
        if (aux < 0.0 || aux > 10.0){
            puts("NOTA INVALIDA! DIGITE NOVAMENTE.");
            continue;
        }
        notas[3] = aux;
        break;
    }

    while(1){
        aux = -1;
        printf("Cadencia: ");
        scanf(" %f", &aux);
        if (aux < 0.0 || aux > 10.0){
            puts("NOTA INVALIDA! DIGITE NOVAMENTE.");
            continue;
        }
        notas[4] = aux;
        break;
    }
}

float media(float notas[]){
    float media;
    media = (notas[0] + 3*notas[1] + 2*notas[2] + 4*notas[3] + 2*notas[4])/12;

    return media;
}


