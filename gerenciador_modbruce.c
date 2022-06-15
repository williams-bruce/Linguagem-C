#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define TRUE 1
#define FALSE 0
#define ARQ "senhas.dat"

typedef struct cadastro{
    char finalidade[21];
    char senha[21];
}CADASTRO;

FILE *fp;

int menu();
void inic();
void get_senha( CADASTRO *pessoa);
void senha_manual(CADASTRO *pessoa);
void senha_automatica(CADASTRO *pessoa);
int oneIsUpper(char senha[]);
int oneIsLower(char senha[]);
int oneIsEspecial(char senha[]);
int oneCharNotAllowed(char senha[]);
int oneisnumeric(char senha[]);
void salvar_senha(CADASTRO pessoa);
int listar_finalidades();
void print_finalidades(CADASTRO pessoa, int contador);
int escolher_finalidade(int cont);
void mostrar_finalidade_senha(int posicao, char PIN[]);
void limpar_tela();
void apagar_senha(int posicao);
int isTherepassword();
void continuar();
int charIsInStr(char c, char str[]);
int confirmar_apagar(int cont);
void senha_gerente(char senha_gerente[]);
void create_change_senha_gerente(char senha_gerente[]);
void changePin(char pin[]);
void confirma_pin(char pin[]);

void main(){
    limpar_tela();
    puts("\n\n*****Bem vindo ao seu gerenciador de senhas!*****\n\n");
    inic();
    char PIN[6];
    senha_gerente(PIN);
    if (isNoPin(PIN)){
        puts("Verificamos que o senhor ainda nao possui um PIN para o seu gerenciador de senhas.\n"
        "Crie um PIN em menu, opcao 4 para ter mais seguranca!");
        continuar();
        limpar_tela();
    }

    
    if (!isTherepassword()){
        puts("\nAinda nao ha senhas salvas!");
    }
    int fica_no_loop = TRUE;
    while (fica_no_loop){
        switch (menu()){
            case 1:{
                CADASTRO pessoa;
                limpar_tela();
                puts("Digite a finalidade da senha: ");
                fflush(stdin);
                gets(pessoa.finalidade);
                get_senha(&pessoa);
                salvar_senha(pessoa);
                limpar_tela();
                printf("Senha salva com sucesso!\n");
                continuar();
                limpar_tela();
                break;
            }
            case 2:{ /* Apresentar senha salva*/
                limpar_tela();
                if (!isTherepassword()){
                    puts("\nAinda nao ha senhas salvas!\n\n");
                    continuar();
                    limpar_tela();
                    break;
                }
                printf("Escolha um numero relativo a senha que deseja visualizar:\n\n");
                int cont = listar_finalidades();
                mostrar_finalidade_senha(escolher_finalidade(cont), PIN);
                continuar();
                limpar_tela();
                break;
            }
            case 3:{ /* Apagar senha*/
                limpar_tela();
                if (!isTherepassword()){
                    puts("\nAinda nao ha senhas salvas!\n\n");
                    continuar();
                    limpar_tela();
                    break;
                }
                printf("Escolha um numero relativo a senha que deseja excluir:\n\n");
                int cont = escolher_finalidade(listar_finalidades());
                limpar_tela();
                if (!confirmar_apagar(cont)){
                    limpar_tela();
                    break;
                }
                apagar_senha(cont);
                limpar_tela();
                puts("Senha apagada com sucesso!");
                continuar();
                limpar_tela();
                break;
            }
            case 4:{/*Troca o PIN do usuário*/
                limpar_tela();
                changePin(PIN);
                continuar();
                limpar_tela();
                break;
            }
            case 5:{/* Sair do programa*/
                fica_no_loop = FALSE;
                break;
            }
            default:{
                limpar_tela();
                continue;
            }
        }
        printf("\n\n");
    }
    puts("Programa encerrado pelo usuario!\n\n");
}

int menu(){ /*Menu principal da aplicação*/
    puts("\n\n**********MENU PRINCIPAL**********");
    puts("Gerenciador de senhas versao 2022!\n\n");
    puts("O que deseja fazer?");
    puts("1 - Criar nova senha");
    puts("2 - Apresentar senha salva");
    puts("3 - Apagar senha salva");
    puts("4 - Trocar PIN do gerenciador de senhas");
    puts("5 - Sair");
    int decisao;
    fflush(stdin);
    scanf("%d", &decisao);
    return decisao;
}

void inic(){/*Verifica se existe o arquivo binário. Se não existir, cria um novo*/
    fp = fopen(ARQ, "r+b");
    if (fp == NULL){
        fp = fopen(ARQ, "w+b");
        if (fp == NULL){
            fprintf(stderr, "Nao foi possivel criar arquivo de dados!!!\n");
            exit(1);
        }
    }
    fclose(fp);
}

void get_senha(CADASTRO *pessoa){/*Menu de escolhar para tipo de entrada de senha*/
    while(1){
        limpar_tela();
        puts("Como deseja gerar sua senha?");
        puts("1 - Digitacao manual");
        puts("2 - Geracao automatica");
        int geracao;
        scanf(" %d", &geracao);
        if (geracao==1){
            limpar_tela();
            senha_manual(pessoa);
            break;
        }
        else if (geracao==2){
            limpar_tela();
            senha_automatica(pessoa);
            break;
        }
        else{
            puts("Entrada invalida. Tente novamente!");
            continue;
        }
    }
}

void senha_manual(CADASTRO *pessoa){/* Verifica se uma senha manual está de acordo com os parâmetros do programa */
    while(TRUE){
        puts("Sua senha deve ter no minimo oito e no maximo 20 caracteres, pelo menos"
        "\numa letra maiuscula, pelo menos uma letra minuscula e um caractere numerico"
        "\nou especial (@, #, $, %, ou &)."
        "\n\nDigite sua senha:");
        int controle = FALSE;
        fflush(stdin);
        
        char a;
	    char senha_auxiliar[21];
        char senha_aux[21];
	    int i = 0;

        while (1) 
	    {
		    a = getch();
		    if (a == 13)
			break ;
		    if (a == 8)
		    {
			    if(i == 0) continue;
			    --i; 
			    system("CLS");
			    printf("Digite a senha: ");
			    for(int a = 0; a < i; a++)
				printf("*");
			    continue;
	        }
		    printf("*");
		    senha_auxiliar[i] = a;
		    i++;
	    }
        fflush(stdin);
        printf("\n");
        fflush(stdin);
	    for(int x = 0; x < i; x++)
		senha_aux[x] = senha_auxiliar[x];
        senha_aux[i] = '\0';
        strcpy(pessoa->senha, senha_aux);

        if (strlen(pessoa->senha)<8){
            puts("Sua senha deve ter no minimo 8 caracteres.");
            controle = TRUE;
        }
        if (!oneIsUpper(pessoa->senha)){
            puts("Sua senha deve ter ao menos uma letra maiuscula!");
            controle = TRUE;
        }
        if (!oneIsLower(pessoa->senha)){
            puts("Sua senha deve ter ao menos uma letra minuscula!");
            controle = TRUE;
        }
        if (!oneIsEspecial(pessoa->senha) && !oneisnumeric(pessoa->senha)){
            puts("Sua senha deve possuir um caracter numerico ou um caractere especial permitido!");
            controle = TRUE;
        }
        if (oneCharNotAllowed(pessoa->senha)){
            puts("Sua senha deve possuir um caractere especial permitido!");
            controle = TRUE;
        }

        if (controle){
            puts("\nAperte ENTER para tentar novamete!\n");
            fflush(stdin);
            getchar();
            limpar_tela();
            continue;
        }
        else{
            break;
        }
    }
}

void senha_automatica(CADASTRO *pessoa){/* Cria uma senha automática segundo os parâmetros do problema */
    char senha_aux[21];
    //letra maiuscula - 40%; letra minuscula - 40%; numero + caracter especial - 20%
    srand((unsigned int)(time(NULL)));
    char numerosEespeciais[] = "0123456789@#$%&";
    char letras_ma[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char letras_mi[] = "abcdefghijklmnopqrstuvwxyz";
    int count_numEesp = 0;
    int count_letras_ma = 0;
    int count_letras_mi = 0;

    //letra maiuscula - 40%; letra minuscula - 40%; numero + caracter especial - 20%
    // para senha de 16 digitos: letra maiuscula - 6; letra minuscula - 7; numero + caracter especial - 3
    for (int i=0;i<16;i++){
        int aleatorio = rand() % 3;
        if (aleatorio==1 && count_letras_ma <7){
            senha_aux[i] = letras_ma[rand() % 26];
            count_letras_ma++;
        }
        else if (aleatorio==2 && count_letras_mi <6){
            senha_aux[i] = letras_mi[rand() % 26];
            count_letras_mi++;
        }
        else if (aleatorio==0 && count_numEesp <3){
            senha_aux[i] = numerosEespeciais[rand() % 15];
            count_numEesp++;
        }
        else{
            --i;
        }
    }
    senha_aux[16] = '\0';
    strcpy(pessoa->senha, senha_aux);
}

int oneIsUpper(char senha[]){ /*Verifica se a senha possui ao menos uma letra maiscula*/
    for (int i=0;senha[i]!='\0';i++){
        if (isupper(senha[i])){
            return TRUE;
        }
    }
    return FALSE;
}

int oneIsLower(char senha[]){ /*Verifica se a senha possui ao menos uma letra minuscula*/
    for (int i=0;senha[i] !='\0';i++){
        if(islower(senha[i])){
            return TRUE;
        }
    }
    return FALSE;
}

int oneIsEspecial(char senha[]){/*Verifica se ao menos um digito na senha é caracter especial*/
    for (int i=0;senha[i] !='\0';i++){
        if (senha[i]=='@'||senha[i]=='#'||senha[i]=='$'||senha[i]=='%'||senha[i]=='&'){
            return TRUE;
        }
    }
    return FALSE;
}

int oneCharNotAllowed(char senha[]){/*Verifica se a senha digitada pelo usuário possui algum caracter inválido*/
    char validos[] = "0123456789@#$%&ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    for (int i=0;senha[i] !='\0';i++){
        if (charIsInStr(senha[i], validos)){
            return FALSE;
        }
    }
    return TRUE;
}

int oneisnumeric(char senha[]){ /*Verifica se ao menos um digito na senha é numérico*/
    for (int i=0;senha[i]!='\0';i++){
        if (isdigit(senha[i])){
            return TRUE;
        }
    }
    return FALSE;
}

void salvar_senha(CADASTRO pessoa){ /*Realiza a persistência dos dados em arquivo binario*/
    fp = fopen(ARQ, "a+b");
    if (fp==NULL){
        puts("Não foi possivel salvar a senha!");
        exit(1);
    }
    if (fwrite(&pessoa, sizeof(CADASTRO),1, fp) != 1){
        printf("Adicionar senha: Falhou a escrita do Registro!\n");
        exit(1);
    }
    fclose(fp);
}

int listar_finalidades(){/*Coloca na tela as finalidades das senhas e retorna a quantidade de senhas*/
    long contador=0;
    CADASTRO info;
    fp = fopen(ARQ, "rb");
    if (fp==NULL){
        puts("Nao foi possivel visualizar as finalidades!!");
        exit(1);
    }
    fseek(fp, (long) sizeof(CADASTRO), SEEK_SET);
    while (1){
        if (fread(&info, sizeof(CADASTRO), 1, fp) != 1){
            break;
        }
        print_finalidades(info, contador);
        contador++;
    }
    fclose(fp);
    return contador;
}

void print_finalidades(CADASTRO pessoa, int contador){/* Mostra ao usuario as finalidades das senhas salvas */
    printf("%3d - %20s\n", contador+1, pessoa.finalidade);
}

int escolher_finalidade(int cont){/*Retorna o numero da finalidade escolhida pelo usuario */
    int escolha = -1;
    while(escolha == -1){
        scanf(" %d", &escolha);
        if (escolha<1 || escolha>cont){
            puts("Valor invalido. Tente novamente!");
            escolha = -1;
            continue;
        }
    }
    return escolha;
}

void mostrar_finalidade_senha(int posicao, char PIN[]){/*Procura a posição da senha e finalidade no arquivo e printa na tela*/
    confirma_pin(PIN);
    CADASTRO info;
    fp = fopen(ARQ, "rb");
    if (fp==NULL){
        puts("Erro na abertura do arquivo!");
        exit(1);
    }
    fseek(fp, (long) posicao*sizeof(CADASTRO), SEEK_SET);

    if (fread(&info, sizeof(CADASTRO), 1, fp) != 1){
        puts("Nao foi possivel ler a informacao solicitada!");
        exit(1);
    }
    limpar_tela();
    puts("**********************************************");
    puts("**********************************************");
    printf("**%42s**\n", " ");
    printf("**     Finalidade: %20s     **\n", info.finalidade);
    printf("**     Senha:      %20s     **\n",info.senha);
    printf("**%42s**\n", " ");
    puts("**********************************************");
    puts("**********************************************");

    fclose(fp);
}

void limpar_tela(){/* Limpa a tela; semelhante ao cls */
    for(int i=0;i<100;i++){
        putchar('\n');
    }
}

void apagar_senha(int posicao){/*Apaga a senha na posição escolhida pelo usuário*/
    CADASTRO info;
    FILE *temp;
    temp = fopen("temp.dat", "wb");
    if (temp==NULL){
        printf("Erro na abertura do arquivo %s!\n", "temp.dat");
        exit(1);
    }

    fp = fopen(ARQ, "rb");
    if (fp==NULL){
        puts("Erro na abertura do arquivo!");
        exit(1);
    }

    fseek(fp, (long) sizeof(CADASTRO), SEEK_SET);
    int count = 1;
    while(fread(&info, sizeof(CADASTRO), 1, fp)==1){
        if (count != posicao){
            if (fwrite(&info, sizeof(CADASTRO), 1, temp)!=1){
                printf("Erro na gravacao do dado %d!\n", count);
                exit(1);
            };
            count++;
        }
        else{
            count++;
        }
    }
    
    fclose(fp);
    fclose(temp);
    remove(ARQ);
    rename("temp.dat", ARQ);
}

int isfempty(){/*Retorna TRUE se o arquivo está vazio, FALSE else*/
    if ((fp = fopen(ARQ, "rb"))==NULL){
        puts("Erro! Nao foi possivel abrir o arquivo!");
        exit(1);
    }
    if (fgetc(fp)!=EOF){
        fclose(fp);
        return FALSE;
    }
    fclose(fp);
    return TRUE;
}

int isTherepassword(){/*Rertorna True se já houver senhas salvas no arquivo. False, else.*/
    if ((fp = fopen(ARQ, "rb"))==NULL){
        puts("Erro! Nao foi possivel abrir o arquivo!");
        exit(1);
    }
    fseek(fp, (long) sizeof(CADASTRO), SEEK_SET);
    if (fgetc(fp)!=EOF){
        fclose(fp);
        return TRUE;
    }
    fclose(fp);
    return FALSE;
}

void continuar(){/*Controle de fluxo para o usuário*/
    puts("Digite enter para continuar...");
    fflush(stdin);
    getchar();
}

int charIsInStr(char c, char str[]){/*Retorna TRUE se se um caracter estiver em uma string, FALSE else*/
    for (int i=0; str[i]!='\0';i++){
        if (str[i] == c){
            return TRUE;
        }
    }
    return FALSE;
}

int confirmar_apagar(int posicao){/*Solicita confirmação para apaga senhas salvas*/
    CADASTRO info;
    fp = fopen(ARQ, "rb");
    if (fp==NULL){
        puts("Erro na abertura do arquivo!");
        exit(1);
    }
    fseek(fp, (long) posicao*sizeof(CADASTRO), SEEK_SET);

    if (fread(&info, sizeof(CADASTRO), 1, fp) != 1){
        puts("Nao foi possivel ler a informacao solicitada!");
        exit(1);
    }

    while(1){
        printf("Confirmar a exclusao da senha de %s?\n", info.finalidade);
        puts("1 - Confirmar exclusao.");
        puts("2 - Retornar ao MENU PRINCIPAL");
        int escolha;
        scanf(" %d", &escolha);
        if (escolha==1){
            fclose(fp);
            return TRUE;
        }
        if (escolha==2){
            fclose(fp);
            return FALSE;
        }
        else{
            limpar_tela();
            puts("Entrada invalida! Tente novamente:");
            continue;
        }
    }
}

void senha_gerente(char senha_gerente[]){
    CADASTRO info;
    if (isfempty()){
        puts("Verificamos que o senhor ainda nao possui uma senha para o seu\n"
        "Gerenciador de Senhas. Crie uma agora para ter maior seguranca!");
        while(1){
            puts("1 - Criar senha para o seu Gerenciador de senhas");
            puts("2 - Continuar sem senha");
            char escolha;
            scanf(" %c", &escolha);
            if (escolha == '1'){
                limpar_tela();
                create_change_senha_gerente(senha_gerente);
                puts("Senha criada com sucesso!");
                puts("Nao esqueca essa senha, pois podera perder suas senhas salvas no Gerenciador de senhas!");
                continuar();
                limpar_tela();

                /*Salvar senha_gerente no arquivo*/
                strcpy(info.senha, senha_gerente);
                strcpy(info.finalidade, "PIN");
                if ((fp = fopen(ARQ, "a+b"))==NULL){
                    puts("Erro na abertura do arquivo!");
                    exit(1);
                }
                rewind(fp);
                if (fwrite(&info, sizeof(CADASTRO), 1, fp)!=1){
                    puts("Erro ao salvar PIN!");
                    exit(1);
                }
                fclose(fp);
                break;
            }
            else if (escolha == '2'){
                puts("Continuando sem senha...");
                strcpy(senha_gerente, "\0");
                strcpy(info.senha, senha_gerente);
                strcpy(info.finalidade, "PIN");
                if ((fp = fopen(ARQ, "r+b"))==NULL){
                    puts("Erro na abertura do arquivo!");
                    exit(1);
                }
                rewind(fp);
                if (fwrite(&info, sizeof(CADASTRO), 1, fp)!=1){
                    puts("Erro em continuar sem senha!");
                    exit(1);
                }
                fclose(fp);
                continuar();
                limpar_tela();
                break;
            }
            else{
                puts("Digito invalido. Tente novamente.");
                continuar();
                limpar_tela();
                continue;
            }
        }
    }
    else{
        if ((fp = fopen(ARQ, "rb"))==NULL){
            puts("Erro na abertura do arquivo!");
            exit(1);
        }
        rewind(fp);
        if (fread(&info, sizeof(CADASTRO), 1, fp)!=1){
            puts("Erro na abertura do arquivo!!!");
        }
        strcpy(senha_gerente, info.senha);
        fclose(fp);
    }
}

void create_change_senha_gerente(char senha_gerente[]){/*Cria o PIN do usuário*/
    char senha_confirmada[6];
    puts("A senha do seu Gerenciador de Senhas deve ter 4 digitos numericos.");
    while(1){
        int senha_ok = TRUE;
        puts("Digite sua senha:");
        fflush(stdin);
        fgets(senha_gerente, 5, stdin);
        for (int i=0; senha_gerente[i]!='\0';i++){
            if (!isdigit(senha_gerente[i])){
                puts("A senha do seu Gerenciador de Senhas deve ter apenas digitos numericos.\n");
                senha_ok = FALSE;
                break;
            }
        }
        if (strlen(senha_gerente)<4){
                puts("Sua senha deve ter 4 digitos!");
                senha_ok = FALSE;
            }
        if (!senha_ok){
            puts("Tente novamente!");
            continuar();
            limpar_tela();
            continue;
        }
        puts("Confirme sua senha:");
        fflush(stdin);
        fgets(senha_confirmada, 5, stdin);
        if (strcmp(senha_confirmada, senha_gerente)){
            puts("As senhas nao sao identicas!\nTente novamente.");
            continuar();
            limpar_tela();
            continue;
        }
        break;
    }
}

void changePin(char pin[]){/*Troca o PIN do gerenciador de senhas*/
    if (strlen(pin)!=0){
        confirma_pin(pin);
    }
    limpar_tela();
    CADASTRO PIN;
    create_change_senha_gerente(pin);
    strcpy(PIN.senha, pin);
    strcpy(PIN.finalidade, "PIN");
    if ((fp = fopen(ARQ, "r+b"))==NULL){
        puts("Erro na abertura para trocar pin!");
        exit(1);
    }
    rewind(fp);
    if ((fwrite(&PIN, sizeof(CADASTRO), 1, fp))!=1){
        puts("Erro na gravacao de novo PIN!");
        exit(1);
    }
    limpar_tela();
    puts("PIN trocado com sucesso!");
    puts("Nao esqueca seu PIN, pois podera perder suas senhas salvas no Gerenciador de senhas!");
    fclose(fp);
}

void confirma_pin(char pin[]){/*Solicita que o usuário digite seu PIN para entrada em locais sensíveis*/
    if (strlen(pin)!=0){
        char tentativa[6];
        int contador = 0;
        while (1){
            puts("Para confirmar, digite o seu PIN:");
            fflush(stdin);
            fgets(tentativa, 5, stdin);
            if (contador == 3){
                puts("PIN digitado incorretamente 3 vezes. O programa sera encerrado...");
                exit(2);
            }
            if (strcmp(pin, tentativa)!=0){
                puts("PIN incorreto! Tente novamente");
                contador++;
                continuar();
                limpar_tela();
                continue;
            }
            break;
        }
    }
}

int isNoPin(char *pin){
    CADASTRO teste;
    if ((fp = fopen(ARQ, "rb"))==NULL){
        puts("Erro na abertura para isNoPin1!");
        exit(1);
    }
    if (fread(&teste, sizeof(CADASTRO), 1, fp)!=1){
        puts("Erro na abertura para isNoPin2!");
        exit(1);
    }
    fclose(fp);
    if (strlen(teste.senha) == 0){
        return TRUE;
    }
    return FALSE;
}

