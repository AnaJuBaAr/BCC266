#ifndef CPU_H
#define CPU_H
#include "RAM.h"
#include "instrucao.h"

typedef struct{
    int registrador1;
    int registrador2;
    int pc;
    Instrucao *programa;
    int opcode;
} CPU;


CPU* criarCPU (){
    CPU *cpu = (CPU*) malloc (sizeof (CPU));
    return cpu;
}
int getRegistrador1 (CPU *c){
    return c->registrador1;
}

void setRegistrador1 (CPU *c, int valor1){
    c->registrador1 = valor1;
}

int getRegistrador2 (CPU *c){
    return c->registrador2;
}

void setRegistrador2 (CPU *c, int valor2){
    c->registrador2 = valor2;
}

void setPrograma (CPU *c, Instrucao *prog){
    c->programa = prog;
}

void iniciarCPU (CPU *c, Ram *ram){
    c->opcode = -100;
    for (c->pc = 0; c->opcode != -1; c->pc++){
        Instrucao inst = c->programa[c->pc];
        c->opcode = inst.opcode;
        switch (c->opcode){
        //halt
        case -1:
            printf ("O programa terminou!\n");
            printRam (ram);
            return;
            break;
        //soma
        case 0: 
            c->registrador1 = getDado (ram, inst.add1);
            c->registrador2 = getDado (ram, inst.add2);
            c->registrador1 += c->registrador2;
            setDado (ram, inst.add3, c->registrador1);
            printf ("SOMA | Ram posicao: %d\t Conteudo: %d\n", inst.add3, c->registrador1);
            break;
        //subtracao
        case 1:
            c->registrador1 = getDado (ram, inst.add1);
            c->registrador2 = getDado (ram, inst.add2);
            c->registrador1 -= c->registrador2;
            setDado (ram, inst.add3, c->registrador1);
            printf ("SUBTRACAO | Ram posicao: %d\t Conteudo: %d\n", inst.add3, c->registrador1);
            break;
        //Copia do Reg para a Ram
        case 2:
            if (inst.add1 == 1){
                setDado (ram, inst.add2, c->registrador1);
                printf ("Registrador1 -> Ram | Ram posicao: %d\t Conteudo: %d\n", inst.add2, c->registrador1);
            }
            else if (inst.add1 == 2){
                setDado (ram, inst.add2, c->registrador2);
                printf ("Registrador2 -> Ram | Ram posicao: %d\t Conteudo: %d\n", inst.add2, c->registrador2);
            }
            break;
        //Copia da Ram para o Reg
        case 3:
            if (inst.add1 == 1){
                c->registrador1 = getDado(ram, inst.add2);
                printf ("Ram [%d] -> Registrador1 | Registrador 1: %d\n", inst.add2,c->registrador1);
            }
            else if (inst.add1 == 2){
                c->registrador2 = getDado(ram, inst.add2);
                printf ("Ram [%d] -> Registrador2 | Registrador 2: %d\n", inst.add2,c->registrador2);
            }
            break;
        }
    }
        
}

CPU* liberarCPU (CPU *c){
    free (c);
    c = NULL;
    return c;
}



#endif