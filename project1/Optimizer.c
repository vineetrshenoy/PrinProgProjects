/*
 *********************************************
 *  314 Principles of Programming Languages  *
 *  Spring 2017                              *
 *  Author: Ulrich Kremer                    *
 *  Student Version                          *
 *********************************************
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "InstrUtils.h"
#include "Utils.h"

Instruction ** outputInstr;


int countInstructions(Instruction * head){
	int count = 0;

	while (head != NULL){
		count++;
		head = head->next;
	}
	return count;
}

int getOutputInstructions(Instruction * head){
	int i = 0;
	int count = 0;
	Instruction * temp = head;

	while (temp != NULL){
		
		if(temp->opcode == OUTPUTAI)
			count++;
		temp = temp->next;
	}

	outputInstr = (Instruction **) malloc(count * sizeof(Instruction *));

	while (head != NULL){
		
		if(head->opcode == OUTPUTAI){
			outputInstr[i] = head;
			i++;
		}
		head = head->next;
	}

	return count;
}


Instruction * findStoreInstr(Instruction * instr ){

	int reg, offset;

	reg = instr->field1;
	offset = instr->field2;
	instr = instr->prev;
	while (instr != NULL){
		if (instr->opcode == STOREAI && instr->field2 == reg && instr->field3 == offset)
			return instr;
		instr = instr->prev;
	}

	return NULL;
}


void getNextCritical(Instruction * instr, int reg){
	OpCode code;
	if (instr == NULL){
		return;
	}
	code = instr->opcode;
	//If the instruction is one of the four arithmetic operations
	if (code == ADD || code == SUB || code == MUL || code == DIV){
		if (reg == instr->field3){
			instr->critical = 'a';
			getNextCritical(instr->prev, instr->field1);
			getNextCritical(instr->prev, instr->field2);

		}
	}

	//If instruction is a LOADI and register match, mark as critical and return immediately
	else if (code == LOADI && reg == instr->field2){
		instr->critical = 'a';
		return;
	}

	//code == LOADAI and registers match, the find the instruction of the first register
	else if (code == LOADAI && reg == instr->field3){
		instr->critical = 'a';
		getNextCritical(instr->prev, instr->field1);
	}
	//STOREAI
	else if (code == STOREAI && reg == instr->field2){
		instr->critical = 'a';
		getNextCritical(instr->prev, instr->field1);
	}

	else 
		getNextCritical(instr->prev, reg);
}

int main()
{
	int outputNum = 0;
	Instruction *head, *temp;
	head = ReadInstructionList(stdin);
	temp = head;
	if (!head) {
		WARNING("No instructions\n");
		exit(EXIT_FAILURE);
	}

	/* YOUR CODE GOES HERE */
	//int instructionCount = countInstructions(head);
	/*
	outputNum = getOutputInstructions(head);
	Instruction * val = findStoreInstr(outputInstr[0]);
	getNextCritical(val->prev, val->field1);
	*/
	while (temp != NULL){
		temp->critical = 'a';
		temp = temp->next;
	}


	if (head) 
		PrintInstructionList(stdout, head);
	
	return EXIT_SUCCESS;
}

