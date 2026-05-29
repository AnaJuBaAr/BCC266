#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "CPU.h"
#include "instrucao.h"
#include "RAM.h"

void programa_aleatorio (Ram *ram, CPU *cpu, int qtdInstrucoes);
int multiplicacao (Ram *ram, CPU *cpu, int multiplicador, int multiplicando);
int divisao (Ram *ram, CPU *cpu, int dividendo, int divisor);
void fibonacci (Ram *ram, CPU *cpu, int Nesimo);
int exponenciacao (Ram *ram, CPU *cpu, int base, int exponte);
int fatorial(Ram *ram, CPU *cpu, int fatorial);
void mdc(Ram *ram, CPU *cpu, int a, int b);
void numero_primo(Ram *ram, CPU *cpu, int x);
int raizQuadrada (Ram *ram, CPU *cpu, int radicando);
int pitagoras(Ram *ram, CPU *cpu, int cat1, int cat2);
int delta (Ram *ram, CPU *cpu, int a, int b, int c);
void bhaskara (Ram *ram, CPU *cpu, int a, int b, int c);
void coeficienteBinomial (Ram *ram, CPU *cpu, int n, int k);

int main (){
    srand (time(NULL));
    CPU *cpu = NULL;
    Ram *ram = NULL;
    //programa_aleatorio (ram, cpu, 200000);
    //multiplicacao (ram, cpu, 15, 10);
    //divisao (ram, cpu, 11, 2);
    //fibonacci (ram, cpu, 30);
    //exponenciacao (ram, cpu, 5, 3);
    //fatorial(ram, cpu, 10);
    //mdc(ram, cpu, 540, 168);
    //numero_primo(ram, cpu, 7);
    //raizQuadrada (ram, cpu, 49);
    //pitagoras (ram, cpu, 45, 72);
    coeficienteBinomial(ram, cpu, 6, 3);

    return 0;
}

void programa_aleatorio (Ram *ram, CPU *cpu, int qtdInstrucoes){
    Instrucao *inst = criarInstrucao (qtdInstrucoes);
    int tamanhoRam = 1000;
    ram = criarRam_aleatoria (tamanhoRam);
    ram = criarRam_aleatoria (tamanhoRam);
    for (int i=0; i < qtdInstrucoes - 1; i++){
        setInstrucao (inst, i, rand () % 1000, rand() % 1000, rand() % 1000, rand() % 2);
    }
    
    setInstrucao (inst, qtdInstrucoes-1, 0, 0, 0, -1);

    cpu = criarCPU ();
    setPrograma (cpu, inst);
    iniciarCPU (cpu, ram);
    cpu = liberarCPU (cpu);
    ram = liberarRam (ram);
    inst = liberarInstrucao (inst);

}

int multiplicacao (Ram *ram, CPU *cpu, int multiplicador, int multiplicando){
    ram = criarRam_vazia (2);
    cpu = criarCPU();
    Instrucao *inst1 = criarInstrucao (2);
    setRegistrador1 (cpu, multiplicando); 
    setInstrucao (inst1, 0, 1, 0, 0, 2); //Registrador 1 para Ram[0]
    setInstrucao (inst1, 1, 0, 0, 0, -1); //Finaliza inst1
    setPrograma (cpu, inst1);
    iniciarCPU (cpu, ram);
    inst1 = liberarInstrucao (inst1);

    for (int i=0; i<multiplicador; i++){
        Instrucao *inst2 = criarInstrucao (2);
        setInstrucao (inst2, 0, 1, 0, 1, 0); //Soma Ram[0] com Ram[1] e armazena em Ram[1]
        setInstrucao (inst2, 1, 0, 0, 0, -1); //Finaliza inst2
        setPrograma (cpu, inst2);
        iniciarCPU (cpu, ram);
        inst2 = liberarInstrucao (inst2);
    }

    Instrucao *inst3 = criarInstrucao (2);
    setInstrucao (inst3, 0, 1, 1, 0, 3); //Ram [1] para Reg1
    setInstrucao (inst3, 1, 0, 0, 0, -1);
    setPrograma (cpu, inst3);
    iniciarCPU (cpu, ram);
    inst3 = liberarInstrucao (inst3);

    printf ("O resultado da multiplicacao eh: %d\n", getRegistrador1(cpu));
    
    int aux = getRegistrador1(cpu);
    cpu = liberarCPU (cpu);
    ram = liberarRam (ram);
    return aux;
}

int divisao (Ram *ram, CPU *cpu, int dividendo, int divisor){
    ram = criarRam_vazia (4);
    cpu = criarCPU ();
    setRegistrador1 (cpu, dividendo);
    setRegistrador2 (cpu, divisor);
    Instrucao *inst1 = criarInstrucao (3);
    setInstrucao (inst1, 0, 1, 0, 0, 2); //Reg1 para Ram[0]
    setInstrucao (inst1, 1, 2, 1, 0, 2); //Reg2 para Ram[1]
    setInstrucao (inst1, 2, -1, -1, -1, -1); //Finalizar inst1
    setPrograma (cpu, inst1);
    iniciarCPU (cpu, ram);
    liberarInstrucao (inst1);
    setRegistrador1 (cpu, 1);
    Instrucao *inst2 = criarInstrucao (2);
    setInstrucao (inst2, 0, 1, 2, 0, 2); //Reg1 para Ram[2]
    setInstrucao (inst2, 1, -1, -1, -1, -1); //Finalizar inst2
    setPrograma (cpu, inst2);
    iniciarCPU (cpu, ram);
    liberarInstrucao (inst2);

    setRegistrador1 (cpu, dividendo);
    while (getRegistrador1(cpu) >= divisor){
        Instrucao *inst3 = criarInstrucao (4);
        setInstrucao (inst3, 0, 0, 1, 0, 1); //Subtrai Ram[0] com Ram[1] e armazeno em Ram[0]
        setInstrucao (inst3, 1, 2, 3, 3, 0); //Somo Ram[2] com Ram[3] e armazeno em Ram[3]
        setInstrucao (inst3, 2, 1, 0, 0, 3); //Ram[0] para Reg1
        setInstrucao (inst3, 3, -1, -1, -1, -1); //Finalizar inst3
        setPrograma (cpu, inst3);
        iniciarCPU (cpu, ram);
        liberarInstrucao (inst3);
    }

    Instrucao *inst4 = criarInstrucao (3);
    setInstrucao (inst4, 0, 1, 3, 0, 3); //Ram[3] para Reg1
    setInstrucao (inst4, 1, 2, 0, 0, 3); //Ram[0] para Reg2
    setInstrucao (inst4, 2, -1, -1, -1, -1); //Finalizar inst4
    setPrograma (cpu, inst4);
    iniciarCPU (cpu, ram);
    liberarInstrucao (inst4);

    printf ("A divisao eh: %d\t Resto da divisao: %d\n ", getRegistrador1(cpu), getRegistrador2(cpu));

    int aux = getRegistrador1(cpu);
    liberarCPU (cpu);
    liberarRam (ram);
    return aux;
}

void fibonacci (Ram *ram, CPU *cpu, int Nesimo){

    ram = criarRam_vazia(3); //0, 1, 2: n-2, n-1, n
    cpu = criarCPU();
    setRegistrador1 (cpu, 1);
    Instrucao *inst1 = criarInstrucao (3);
    setInstrucao (inst1, 0, 1, 0, -1, 2); //Reg1 para Ram[0]
    setInstrucao (inst1, 1, 1, 2, -1, 2); //Reg1 para Ran[2]
    setInstrucao (inst1, 2, -1, -1, -1, -1); //Finalizar inst1
    setPrograma (cpu, inst1);
    iniciarCPU (cpu, ram);
    liberarInstrucao (inst1);

    for (int i=Nesimo; i > 1; i--){
        Instrucao *inst2 = criarInstrucao (6);
        setInstrucao (inst2, 0, 0, 1, 2, 0); //Soma Ram[0] com Ram[1] e armazena em Ram[2]
        setInstrucao (inst2, 1, 1, 0, -1, 3); //Ram[0] para Reg1
        setInstrucao (inst2, 2, 1, 1, -1, 2); //Reg1 para Ram[1]
        setInstrucao (inst2, 3, 1, 2, -1, 3); //Ram[2] para Reg1
        setInstrucao (inst2, 4, 1, 0, -1, 2); //Reg1 para Ram[0]
        setInstrucao (inst2, 5, -1, -1, -1, -1); //Finaliza inst2
        setPrograma (cpu, inst2);
        iniciarCPU (cpu, ram);
        liberarInstrucao (inst2);
    }

    Instrucao *inst3 = criarInstrucao(2);
    setInstrucao (inst3, 0, 1, 2, -1, 3); //Ram[2] para Reg1
    setInstrucao (inst3, 1, -1, -1, -1, -1); //Finaliza inst3
    setPrograma (cpu, inst3);
    iniciarCPU (cpu, ram);
    liberarInstrucao (inst3);
    printf ("O %d-esimo termo da sequencia de Fibonacci eh: %d\n", Nesimo, getRegistrador1(cpu));
}

int exponenciacao (Ram *ram, CPU *cpu, int base, int exponte){
    ram = criarRam_vazia (2);
    cpu = criarCPU ();
    setRegistrador1 (cpu, base);
    setRegistrador2 (cpu, 1);
    Instrucao *inst1 = criarInstrucao (3);
    setInstrucao (inst1, 0, 1, 0, -1, 2); //Reg1 para Ram[0]
    setInstrucao (inst1, 1, 2, 1, -1, 2); //Reg2 para Ram[1]
    setInstrucao (inst1, 2, -1, -1, -1, -1); //Finalizar inst1
    setPrograma (cpu, inst1);
    iniciarCPU (cpu, ram);
    liberarInstrucao (inst1);

    for (int i=exponte; i > 0; i--){
        Instrucao *inst2 = criarInstrucao (3);
        setInstrucao (inst2, 0, 1, 0, -1, 3); //Ram[0] para Reg1
        setInstrucao (inst2, 1, 2, 1, -1, 3); //Ram[1] para Reg2
        setInstrucao (inst2, 2, -1, -1, -1, -1); //Finalizar inst2
        setPrograma (cpu, inst2);
        iniciarCPU (cpu, ram);
        liberarInstrucao (inst2);
        setRegistrador1(cpu, multiplicacao (NULL, NULL, getRegistrador1(cpu), getRegistrador2(cpu)));
        Instrucao *inst3 = criarInstrucao (2);
        setInstrucao (inst3, 0, 1, 1, -1, 2); //Reg1 para Ram[1]
        setInstrucao (inst3, 1, -1, -1, -1, -1); //Finalizar inst3
        setPrograma (cpu, inst3);
        iniciarCPU (cpu, ram);
        liberarInstrucao (inst3);
    }

    Instrucao *inst4 = criarInstrucao (2);
    setInstrucao (inst4, 0, 1, 1, -1, 3); //Ram[1] para Reg1
    setInstrucao (inst4, 1, 0, 0, 0, -1); //Finalizar inst4
    setPrograma (cpu, inst4);
    iniciarCPU (cpu, ram);
    inst4 = liberarInstrucao (inst4);
    
    printf ("O resultado da esponenciacao eh: %d\n", getRegistrador1(cpu));
    int aux = getRegistrador1(cpu);
    liberarCPU (cpu);
    liberarRam (ram);
    return aux;
}

int fatorial(Ram *ram, CPU *cpu, int fatorial){
    ram = criarRam_vazia(2);
    cpu = criarCPU();
    
    Instrucao *inst1 = criarInstrucao(2);
    setRegistrador1(cpu, 1);
    setInstrucao(inst1, 0, 1, 0, -1, 2);
    setInstrucao(inst1, 1, -1, -1, -1, -1);
    setPrograma(cpu, inst1);
    iniciarCPU(cpu, ram);
    liberarInstrucao(inst1);

    for(int i = 2; i <= fatorial; i++){
        Instrucao *inst2 = criarInstrucao(2);
        setRegistrador1(cpu, i);
        setInstrucao(inst2, 0, 1, 1, -1, 2);
        setInstrucao(inst2, 1, -1, -1, -1, -1);
        setPrograma(cpu, inst2);
        iniciarCPU(cpu, ram);
        liberarInstrucao(inst2);

        Instrucao *inst3 = criarInstrucao(3);
        setInstrucao(inst3, 0, 1, 0, -1, 3);
        setInstrucao(inst3, 1, 2, 1, -1, 3);
        setInstrucao(inst3, 2, -1, -1, -1, -1);
        setPrograma(cpu, inst3);
        iniciarCPU(cpu, ram);
        liberarInstrucao(inst3);

        setRegistrador1(cpu, multiplicacao(NULL, NULL, getRegistrador1(cpu), getRegistrador2(cpu)));

        Instrucao *inst4 = criarInstrucao(2);
        setInstrucao(inst4, 0, 1, 0, -1, 2);
        setInstrucao(inst4, 1, -1, -1, -1, -1);
        setPrograma(cpu, inst4);
        iniciarCPU(cpu, ram);
        liberarInstrucao(inst4);
    }
    
    printf("O resultado do fatorial de %d eh: %d\n", fatorial, getRegistrador1(cpu));
    int aux = getRegistrador1(cpu);
    liberarCPU(cpu);
    liberarRam(ram);
    return aux;
}

void mdc(Ram *ram, CPU *cpu, int a, int b){
    cpu = criarCPU();
    ram = criarRam(4);

    setRegistrador1(cpu, a);
    setRegistrador2(cpu, b);

    while(getRegistrador2(cpu) != 0){
        setRegistrador1(cpu, divisao(NULL, NULL, getRegistrador1(cpu), getRegistrador2(cpu)));
        
        Instrucao *inst2 = criarInstrucao(3);
        setInstrucao(inst2, 0, 2, 0, -1, 2);
        setInstrucao(inst2, 1, 1, 1, -1, 2);
        setInstrucao(inst2, 2, -1, -1, -1, -1);
        setPrograma(cpu, inst2);
        iniciarCPU(cpu, ram);
        liberarInstrucao(inst2);

        Instrucao *inst3 = criarInstrucao(3);
        setInstrucao(inst3, 0, 1, 0, -1, 3);
        setInstrucao(inst3, 1, 2, 1, -1, 3);
        setInstrucao(inst3, 2, -1, -1, -1, -1);
        setPrograma(cpu, inst3);
        iniciarCPU(cpu, ram);
        liberarInstrucao(inst3);
    }

    printf("MDC = %d\n", getRegistrador1(cpu));
}

void numero_primo(Ram *ram, CPU *cpu, int x){
    ram = criarRam_vazia(2);
    cpu = criarCPU();

    setRegistrador1(cpu, x);

    if(getRegistrador1(cpu) <= 2){
        printf("O numero %d é primo\n", getRegistrador1(cpu));
        
        liberarCPU(cpu);
        liberarRam(ram);

        return;
    }

    for(int i = 2; i < getRegistrador1(cpu); i++){
        if(divisao(NULL, NULL, getRegistrador1(cpu), i) == 0){
            printf("Numero %d não é primo\n", getRegistrador1(cpu));
            
            liberarCPU(cpu);
            liberarRam(ram);
            
            return;
        }
    }
    printf("O numero %d é primo\n", getRegistrador1(cpu));

    liberarCPU(cpu);
    liberarRam(ram);
}

int raizQuadrada (Ram *ram, CPU *cpu, int radicando){
    ram = criarRam_vazia (4); // [0] = N; [1] = 1; [2] = Radicando; [3] = ResMult
    cpu = criarCPU ();
    setRegistrador1 (cpu, radicando);
    setRegistrador2 (cpu, 1);
    Instrucao *inst1 = criarInstrucao (4);
    setInstrucao (inst1, 0, 1, 2, -1, 2); //Reg1 para Ram[2]
    setInstrucao (inst1, 1, 2, 1, -1, 2); //Reg2 para Ram[1]
    setInstrucao (inst1, 2, 1, 0, -1, 3); //Ram[0] para Reg1
    setInstrucao (inst1, 3, -1, -1, -1, -1); //Finalizar inst1
    setPrograma (cpu, inst1);
    iniciarCPU (cpu, ram);
    liberarInstrucao (inst1);

    while (getRegistrador1(cpu) < radicando){
        Instrucao *inst2 = criarInstrucao (2);
        setInstrucao (inst2, 0, 1, 0, 0, 0); //Soma Ram[0] com Ram[1]
        setInstrucao (inst2, 1, -1, -1, -1, -1); //Finalizar inst3
        setPrograma (cpu, inst2);
        iniciarCPU (cpu, ram);
        liberarInstrucao (inst2);

        Instrucao *inst3 = criarInstrucao (3);
        setInstrucao (inst3, 0, 1, 0, -1, 3); //Ram[0] para Reg1
        setInstrucao (inst3, 1, 2, 0, -1, 3); //Ram[0] para Reg2
        setInstrucao (inst3, 2, -1, -1, -1, -1); //Finalizar inst3
        setPrograma (cpu, inst3);
        iniciarCPU (cpu, ram);
        liberarInstrucao (inst3);

        setRegistrador1 (cpu, multiplicacao(NULL, NULL, getRegistrador1(cpu), getRegistrador2(cpu)));

        Instrucao *inst4 = criarInstrucao (2);
        setInstrucao (inst4, 0, 1, 3, -1, 2); //Reg1 para Ram[3]
        setInstrucao (inst4, 1, -1, -1, -1, -1); //Finalizar inst4
        setPrograma (cpu, inst4);
        iniciarCPU (cpu, ram);
        liberarInstrucao (inst4);
        printf("Registrador1: %d\n", getRegistrador1(cpu));
    }

    Instrucao *inst5 = criarInstrucao (2);
    setInstrucao (inst5, 0, 1, 0, -1, 3); //Ram[0] para Reg1
    setInstrucao (inst5, 1, -1, -1, -1, -1); //Finalizar inst5
    setPrograma (cpu, inst5);
    iniciarCPU (cpu, ram);
    liberarInstrucao (inst5);

    printf ("A raiz do numero eh: %d\n", getRegistrador1(cpu));
    int aux = getRegistrador1 (cpu);
    liberarCPU (cpu);
    liberarRam (ram);
    return aux;
}

int pitagoras (Ram *ram, CPU *cpu, int cat1, int cat2){
    ram = criarRam_vazia (3);
    cpu = criarCPU ();

    //calcula cat1²
    setRegistrador1 (cpu, cat1);
    setRegistrador2 (cpu, 2);
    setRegistrador1 (cpu, exponenciacao(NULL, NULL, getRegistrador1(cpu), getRegistrador2(cpu)));

    //guarda cat1² na ram[0]
    Instrucao *inst1 = criarInstrucao (2);
    setInstrucao (inst1, 0, 1, 0, -1, 2);
    setInstrucao (inst1, 1, -1, -1, -1, -1);
    setPrograma(cpu, inst1);
    iniciarCPU (cpu, ram);
    liberarInstrucao (inst1);

    //calcula cat2²
    setRegistrador1 (cpu, cat2);
    setRegistrador2 (cpu, 2);
    setRegistrador1 (cpu, exponenciacao(NULL, NULL, getRegistrador1(cpu), getRegistrador2(cpu)));

    //guarda cat2² na ram[1]
    Instrucao *inst2 = criarInstrucao (2);
    setInstrucao (inst2, 0, 1, 1, -1, 2);
    setInstrucao (inst2, 1, -1, -1, -1, -1);
    setPrograma(cpu, inst2);
    iniciarCPU (cpu, ram);
    liberarInstrucao (inst2);

    //ram[0] = ram[0] + ram[1]
    Instrucao *inst3 = criarInstrucao (2);
    setInstrucao (inst3, 0, 0, 1, 0, 0);
    setInstrucao (inst3, 1, -1, -1, -1, -1);
    setPrograma(cpu, inst3);
    iniciarCPU (cpu, ram);
    liberarInstrucao (inst3);

    //reg1 = ram[0]
    Instrucao *inst4 = criarInstrucao (2);
    setInstrucao (inst4, 0, 1, 0, -1, 3);
    setInstrucao (inst4, 1, -1, -1, -1, -1);
    setPrograma(cpu, inst4);
    iniciarCPU (cpu, ram);
    liberarInstrucao (inst4);

    //calcula raiz(reg1)
    setRegistrador1 (cpu, raizQuadrada(NULL, NULL, getRegistrador1(cpu)));
    //guarda reg1 na ram[0]
    Instrucao *inst5 = criarInstrucao (2);
    setInstrucao (inst5, 0, 1, 0, -1, 2);
    setInstrucao (inst5, 1, -1, -1, -1, -1);
    setPrograma(cpu, inst5);
    iniciarCPU (cpu, ram);
    liberarInstrucao (inst5);

    //reg1 = ram[0]
    Instrucao *inst6 = criarInstrucao (2);
    setInstrucao (inst6, 0, 1, 0, -1, 3);
    setInstrucao (inst6, 1, -1, -1, -1, -1);
    setPrograma(cpu, inst6);
    iniciarCPU (cpu, ram);
    liberarInstrucao (inst6);

    printf ("A hipotenusa eh aproximadamente: %d\n", getRegistrador1 (cpu));
    int aux = getRegistrador1 (cpu);
    liberarCPU (cpu);
    liberarRam (ram);
    return aux;
}

int delta (Ram *ram, CPU *cpu, int a, int b, int c){
    ram = criarRam_vazia(3);
    cpu = criarCPU();

    setRegistrador1(cpu, a);
    setRegistrador2(cpu, c);

    //calcula a*c
    setRegistrador1(cpu, multiplicacao(NULL, NULL, getRegistrador1(cpu), getRegistrador2(cpu)));
    //calcula 4*a*c
    setRegistrador2(cpu, multiplicacao(NULL, NULL, 4, getRegistrador1(cpu)));

    //calcula b²
    setRegistrador1(cpu, b);
    setRegistrador1(cpu, exponenciacao(NULL, NULL, getRegistrador1(cpu), 2));

    //copia b² para ram[0] e 4*a*c para ram[1]
    Instrucao *inst1 = criarInstrucao(3);
    setInstrucao(inst1, 0, 1, 0, -1, 2);
    setInstrucao(inst1, 1, 2, 1, -1, 2);
    setInstrucao(inst1, 2, -1, -1, -1, -1);
    setPrograma(cpu, inst1);
    iniciarCPU(cpu, ram);
    liberarInstrucao(inst1);

    //calcula b² - 4*a*c
    Instrucao *inst2 = criarInstrucao(2);
    setInstrucao(inst2, 0, 0, 1, -1, 1);
    setInstrucao(inst2, 1, -1, -1, -1, -1);
    setPrograma(cpu, inst2);
    iniciarCPU(cpu, ram);
    liberarInstrucao(inst2);

    Instrucao *inst3 = criarInstrucao(2);
    setInstrucao(inst3, 0, 1, 0, -1, 3);
    setInstrucao(inst3, 1, -1, -1, -1, -1);
    setPrograma(cpu, inst3);
    iniciarCPU(cpu, ram);
    liberarInstrucao(inst3);

    printf("O valor de delta é: %d\n", getRegistrador1(cpu));
    int aux = getRegistrador1(cpu);
    liberarCPU(cpu);
    liberarRam(ram);
    return aux;
}

void bhaskara (Ram *ram, CPU *cpu, int a, int b, int c){
    //calcula o delta
    
    ram = criarRam_vazia(3);
    cpu = criarCPU();
    setRegistrador1(cpu, delta(NULL, NULL, a, b, c));
    
    if(getRegistrador1(cpu) < 0){
        printf("A equação não possui raízes reais.\n");
        liberarCPU(cpu);
        liberarRam(ram);
        return;
    } else if(getRegistrador1(cpu) == 0){
        //calcula -b
        setRegistrador2(cpu, multiplicacao(NULL, NULL, -1, b));

        //calcula raiz quadrada de delta
        setRegistrador1(cpu, raizQuadrada(NULL, NULL, getRegistrador1(cpu)));

        //copia -b para ram[0] e raiz de delta para ram[1]
        Instrucao *inst1 = criarInstrucao(3);
        setInstrucao(inst1, 0, 2, 0, -1, 2);
        setInstrucao(inst1, 1, 1, 1, -1, 2);
        setInstrucao(inst1, 2, -1, -1, -1, -1);
        setPrograma(cpu, inst1);
        iniciarCPU(cpu, ram);
        liberarInstrucao(inst1);

        //soma -b com raiz de delta
        Instrucao *inst2 = criarInstrucao(2);
        setInstrucao(inst2, 0, 0, 1, 0, 0);
        setInstrucao(inst2, 1, -1, -1, -1, -1);
        setPrograma(cpu, inst2);
        iniciarCPU(cpu, ram);
        liberarInstrucao(inst2);

        //copia -b+raiz(delta) para reg1
        Instrucao *inst3 = criarInstrucao(2);
        setInstrucao(inst3, 0, 1, 0, -1, 3);
        setInstrucao(inst3, 1, -1, -1, -1, -1);
        setPrograma(cpu, inst3);
        iniciarCPU(cpu, ram);
        liberarInstrucao(inst3);

        //calcula 2a
        setRegistrador2(cpu, multiplicacao(NULL, NULL, 2, a));

        //calcula (-b + raiz(delta)) / 2a
        setRegistrador1(cpu, divisao(NULL, NULL, getRegistrador1(cpu), getRegistrador2(cpu)));

        printf("A raiz da equação é: %d\n", getRegistrador1(cpu));

        liberarCPU(cpu);
        liberarRam(ram);
        return;
    }
    //calcula -b
    setRegistrador2(cpu, multiplicacao(NULL, NULL, -1, b));

    //calcula raiz quadrada de delta
    setRegistrador1(cpu, raizQuadrada(NULL, NULL, getRegistrador1(cpu)));

    Instrucao *inst2 = criarInstrucao(3);
    //soma -b com raiz(delta) e guarda em ram[0]
    setInstrucao(inst2, 0, 0, 1, 0, 0);
    //subtrai -b com raiz(delta) e guarda em ram[1]
    setInstrucao(inst2, 1, 0, 1, 1, 1);
    setInstrucao(inst2, 2, -1, -1, -1, -1);
    setPrograma(cpu, inst2);
    iniciarCPU(cpu, ram);
    liberarInstrucao(inst2);

    //copia (-b + raiz(delta)) para reg1
    Instrucao *inst3 = criarInstrucao(2);
    setInstrucao(inst3, 0, 1, 0, -1, 3);
    setInstrucao(inst3, 1, -1, -1, -1, -1);
    setPrograma(cpu, inst3);
    iniciarCPU(cpu, ram);
    liberarInstrucao(inst3);

    //copia (-b - raiz(delta)) para reg2
    Instrucao *inst4 = criarInstrucao(2);
    setInstrucao(inst4, 0, 2, 1, -1, 3);
    setInstrucao(inst4, 1, -1, -1, -1, -1);
    setPrograma(cpu, inst4);
    iniciarCPU(cpu, ram);
    liberarInstrucao(inst4);

    //calcula (-b + raiz(delta)) / 2a
    setRegistrador1(cpu, divisao(NULL, NULL, getRegistrador1(cpu), multiplicacao(NULL, NULL, 2, a)));

    //calcula (-b - raiz(delta)) / 2a
    setRegistrador2(cpu, divisao(NULL, NULL, getRegistrador2(cpu), multiplicacao(NULL, NULL, 2, a)));

    printf("As raizes da equação são: %d e %d\n", getRegistrador1(cpu), getRegistrador2(cpu));

    liberarCPU(cpu);
    liberarRam(ram);
}

void coeficienteBinomial (Ram *ram, CPU *cpu, int n, int k){
    ram = criarRam_vazia(5);
    cpu = criarCPU();

    //Colocando n e k na ram
    setRegistrador1(cpu, n);
    setRegistrador2(cpu, k);
    Instrucao *inst1 = criarInstrucao(3);
    setInstrucao(inst1, 0, 1, 0, -1, 2);
    setInstrucao(inst1, 1, 2, 1, -1, 2);
    setInstrucao(inst1, 2, -1, -1, -1, -1);
    setPrograma(cpu, inst1);
    iniciarCPU(cpu, ram);
    liberarInstrucao(inst1);

    //Fatorial de n! e k!
    Instrucao *inst2 = criarInstrucao(3);
    setInstrucao(inst2, 0, 1, 0, -1, 3);
    setInstrucao(inst2, 1, 2, 1, -1, 3);
    setInstrucao(inst2, 2, -1, -1, -1, -1);
    setPrograma(cpu, inst2);
    iniciarCPU(cpu, ram);
    liberarInstrucao(inst2);
    setRegistrador1(cpu, fatorial(NULL, NULL, getRegistrador1(cpu)));
    setRegistrador2(cpu, fatorial(NULL, NULL, getRegistrador2(cpu)));
    Instrucao *inst3 = criarInstrucao(3);
    setInstrucao(inst3, 0, 1, 2, -1, 2);
    setInstrucao(inst3, 1, 2, 3, -1, 2);
    setInstrucao(inst3, 2, -1, -1, -1, -1);
    setPrograma(cpu, inst3);
    iniciarCPU(cpu, ram);
    liberarInstrucao(inst3);

    //Subtraindo (n-k)
    Instrucao *inst4 = criarInstrucao(2);
    setInstrucao(inst4, 0, 0, 1, 1, 1);
    setInstrucao(inst4, 1, -1, -1, -1, -1);
    setPrograma(cpu, inst4);
    iniciarCPU(cpu, ram);
    liberarInstrucao(inst4);

    //Fatorial de (n-k)!
    Instrucao *inst5 = criarInstrucao(2);
    setInstrucao(inst5, 0, 1, 1, -1, 3);
    setInstrucao(inst5, 1, -1, -1, -1, -1);
    setPrograma(cpu, inst5);
    iniciarCPU(cpu, ram);
    liberarInstrucao(inst5);
    setRegistrador1(cpu, fatorial(NULL, NULL, getRegistrador1(cpu)));
    Instrucao *inst6 = criarInstrucao(2);
    setInstrucao(inst6, 0, 1, 1, -1, 2);
    setInstrucao(inst6, 1, -1, -1, -1, -1);
    setPrograma(cpu, inst6);
    iniciarCPU(cpu, ram);
    liberarInstrucao(inst6);

    //Multiplicando k! * (n-k)!
    Instrucao *inst7 = criarInstrucao(3);
    setInstrucao(inst7, 0, 1, 3, -1, 3);
    setInstrucao(inst7, 1, 2, 1, -1, 3);
    setInstrucao(inst7, 2, -1, -1, -1, -1);
    setPrograma(cpu, inst7);
    iniciarCPU(cpu, ram);
    liberarInstrucao(inst7);
    printf("\n\noi\n\n");
    setRegistrador1(cpu, multiplicacao(NULL, NULL, getRegistrador1(cpu), getRegistrador2(cpu)));
    Instrucao *inst8 = criarInstrucao(2);
    setInstrucao(inst8, 0, 1, 1, -1, 2);
    setInstrucao(inst8, 1, -1, -1, -1, -1);
    setPrograma(cpu, inst8);
    iniciarCPU(cpu, ram);
    liberarInstrucao(inst8);

    //Dividindo n! / k! * (n-k)!
    Instrucao *inst9 = criarInstrucao(3);
    setInstrucao(inst9, 0, 1, 2, -1, 3);
    setInstrucao(inst9, 1, 2, 1, -1, 3);
    setInstrucao(inst9, 2, -1, -1, -1, -1);
    setPrograma(cpu, inst9);
    iniciarCPU(cpu, ram);
    liberarInstrucao(inst9);
    setRegistrador1(cpu, divisao(NULL, NULL, getRegistrador1(cpu), getRegistrador2(cpu)));
    Instrucao *inst10 = criarInstrucao(2);
    setInstrucao(inst10, 0, 1, 0, -1, 2);
    setInstrucao(inst10, 1, -1, -1, -1, -1);
    setPrograma(cpu, inst10);
    iniciarCPU(cpu, ram);
    liberarInstrucao(inst10);

    Instrucao *inst11 = criarInstrucao(2);
    setInstrucao(inst11, 0, 1, 0, -1, 3);
    setInstrucao(inst11, 1, -1, -1, -1, -1);
    setPrograma(cpu, inst11);
    iniciarCPU(cpu, ram);
    liberarInstrucao(inst11);
    printf("O resultado da combinacao eh: %d\n", getRegistrador1(cpu));

    liberarCPU(cpu);
    liberarRam(ram);
}