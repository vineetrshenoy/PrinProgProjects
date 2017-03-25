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
			head->critical = '1';
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
		if (instr->opcode == STOREAI && instr->field2 == reg && instr->field3 == offset){
			instr->critical = '1';
			return instr;
		}
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
	if ((code == ADD || code == SUB || code == MUL || code == DIV) && (reg == instr->field3)){
			instr->critical = '1';
			getNextCritical(instr->prev, instr->field1);
			getNextCritical(instr->prev, instr->field2);

		
	}

	//If instruction is a LOADI and register match, mark as critical and return immediately
	else if (code == LOADI && reg == instr->field2){
		instr->critical = '1';
		return;
	}

	//code == LOADAI and registers match, the find the instruction of the first register
	else if (code == LOADAI && reg == instr->field3){
		instr->critical = '1';
		Instruction * store = findStoreInstr(instr);
		getNextCritical(store->prev, store->field1);
	}
	//STOREAI
	
	else if (code == STOREAI && reg == instr->field2){
		instr->critical = '1';
		getNextCritical(instr->prev, instr->field1);
	}
	
	else 
		getNextCritical(instr->prev, reg);
}

void preserveCritical(Instruction * head){

	if (head == NULL)
		return;

	Instruction * previous = head;
	Instruction * current = head->next;
	Instruction * last;

	while (current != NULL){

		if (previous->critical == '1' && current->critical == '0'){

			while (current != NULL && current->critical == '0'){
				
				if (current->next == NULL)
					last = current;

				current = current->next;

				if (current != NULL)
					free(current->prev);
			}

			if (current == NULL)
				free(last);
			
			else
				current->prev = previous;
			
			previous->next = current;

		}

		previous = current;
		current = current->next;
	}
}




int main()
{
	int outputNum = 0;
	int i = 0;
	Instruction *head, *temp;
	head = ReadInstructionList(stdin);
	temp = head;
	if (!head) {
		WARNING("No instructions\n");
		exit(EXIT_FAILURE);
	}
	while (temp != NULL){
		temp->critical = '0';
		temp = temp->next;
	}
	head->critical = '1'; //the first instruction is  always critical
	/* YOUR CODE GOES HERE */
	//int instructionCount = countInstructions(head);
	
	outputNum = getOutputInstructions(head);
	for (i = 0; i < outputNum; i++){
		Instruction * val = findStoreInstr(outputInstr[i]);
		getNextCritical(val->prev, val->field1);
	}
	

	preserveCritical(head);

	
	free(outputInstr);
		


	if (head) 
		PrintInstructionList(stdout, head);
	
	return EXIT_SUCCESS;
}

