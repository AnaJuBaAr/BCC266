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
void fatorial(Ram *ram, CPU *cpu, int fatorial);
void mdc(Ram *ram, CPU *cpu, int a, int b);
void numero_primo(Ram *ram, CPU *cpu, int x);
int raizQuadrada (Ram *ram, CPU *cpu, int radicando);
int pitagoras(Ram *ram, CPU *cpu, int cat1, int cat2);
void bhaskara (Ram *ram, CPU *cpu, int a, int b, int c);

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
    //raizQuadrada (ram, cpu, 36);
    pitagoras (ram, cpu, 45, 72);

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

    printf ("O resultado da multiplicacao eh: %d\n", cpu->registrador1);
    
    int aux = cpu->registrador1;
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
    while (cpu->registrador1 >= divisor){
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

    printf ("A divisao eh: %d\t Resto da divisao: %d\n ", cpu->registrador1, cpu->registrador2);

    int aux = cpu->registrador2;
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
    printf ("O %d-esimo termo da sequencia de Fibonacci eh: %d\n", Nesimo, cpu->registrador1);
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
        cpu->registrador1 = multiplicacao (ram, cpu, cpu->registrador1, cpu->registrador2);
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

void fatorial(Ram *ram, CPU *cpu, int fatorial){
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

        cpu->registrador1 = multiplicacao(ram, cpu, cpu->registrador1, cpu->registrador2);

        Instrucao *inst4 = criarInstrucao(2);
        setInstrucao(inst4, 0, 1, 0, -1, 2);
        setInstrucao(inst4, 1, -1, -1, -1, -1);
        setPrograma(cpu, inst4);
        iniciarCPU(cpu, ram);
        liberarInstrucao(inst4);
    }
    
    printf("O resultado do fatorial de %d eh: %d\n", fatorial, cpu->registrador1);

    liberarCPU(cpu);
    liberarRam(ram);
}

void mdc(Ram *ram, CPU *cpu, int a, int b){
    cpu = criarCPU();
    ram = criarRam(4);

    setRegistrador1(cpu, a);
    setRegistrador2(cpu, b);

    while(cpu->registrador2 != 0){
        setRegistrador1(cpu, divisao(ram, cpu, cpu->registrador1, cpu->registrador2));
        
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

    printf("MDC = %d\n", cpu->registrador1);
}

void numero_primo(Ram *ram, CPU *cpu, int x){
    ram = criarRam_vazia(2);
    cpu = criarCPU();

    setRegistrador1(cpu, x);

    if(cpu->registrador1 <= 2){
        printf("O numero %d é primo\n", cpu->registrador1);
        
        liberarCPU(cpu);
        liberarRam(ram);

        return;
    }

    for(int i = 2; i < cpu->registrador1; i++){
        if(divisao(ram, cpu, cpu->registrador1, i) == 0){
            printf("Numero %d não é primo\n", cpu->registrador1);
            
            liberarCPU(cpu);
            liberarRam(ram);
            
            return;
        }
    }
    printf("O numero %d é primo\n", cpu->registrador1);

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

        setRegistrador1 (cpu, multiplicacao(ram, cpu, getRegistrador1(cpu), getRegistrador2(cpu)));

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
    setRegistrador1 (cpu, cat1);
    setRegistrador2 (cpu, 2);
    setRegistrador1 (cpu, exponenciacao(ram, cpu, getRegistrador1(cpu), getRegistrador2(cpu)));

    Instrucao *inst1 = criarInstrucao (2);
    setInstrucao (inst1, 0, 1, 0, -1, 2);
    setInstrucao (inst1, 1, -1, -1, -1, -1);
    setPrograma(cpu, inst1);
    iniciarCPU (cpu, ram);
    liberarInstrucao (inst1);

    setRegistrador1 (cpu, cat2);
    setRegistrador2 (cpu, 2);
    setRegistrador1 (cpu, exponenciacao(ram, cpu, getRegistrador1(cpu), getRegistrador2(cpu)));

    Instrucao *inst2 = criarInstrucao (2);
    setInstrucao (inst2, 0, 1, 1, -1, 2);
    setInstrucao (inst2, 1, -1, -1, -1, -1);
    setPrograma(cpu, inst2);
    iniciarCPU (cpu, ram);
    liberarInstrucao (inst2);

    Instrucao *inst3 = criarInstrucao (2);
    setInstrucao (inst3, 0, 0, 1, 0, 0);
    setInstrucao (inst3, 1, -1, -1, -1, -1);
    setPrograma(cpu, inst3);
    iniciarCPU (cpu, ram);
    liberarInstrucao (inst3);

    Instrucao *inst4 = criarInstrucao (2);
    setInstrucao (inst4, 0, 1, 0, -1, 3);
    setInstrucao (inst4, 1, -1, -1, -1, -1);
    setPrograma(cpu, inst4);
    iniciarCPU (cpu, ram);
    liberarInstrucao (inst4);

    setRegistrador1 (cpu, raizQuadrada(ram, cpu, getRegistrador1(cpu)));
    Instrucao *inst5 = criarInstrucao (2);
    setInstrucao (inst5, 0, 1, 0, -1, 2);
    setInstrucao (inst5, 1, -1, -1, -1, -1);
    setPrograma(cpu, inst5);
    iniciarCPU (cpu, ram);
    liberarInstrucao (inst5);

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

void bhaskara (Ram *ram, CPU *cpu, int a, int b, int c){
    ram = criarRam_vazia (10);
    cpu = criarCPU ();
    
}