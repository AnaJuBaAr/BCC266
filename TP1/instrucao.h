#ifndef INSTRUCAO_H
#define INSTRUCAO_H

typedef struct {
    int add1;
    int add2;
    int add3;
    int opcode;
} Instrucao;

Instrucao* criarInstrucao (int qtdInstrucao){
    Instrucao *inst = (Instrucao*) malloc (qtdInstrucao * sizeof (Instrucao));
    return inst;
}

void setInstrucao (Instrucao *inst, int indice, int add1, int add2, int add3, int opcode){
    inst[indice].add1 = add1;
    inst[indice].add2 = add2;
    inst[indice].add3 = add3;
    inst[indice].opcode = opcode;
}

Instrucao* liberarInstrucao (Instrucao *inst){
    free (inst);
    inst = NULL;
    return inst;
}
#endif