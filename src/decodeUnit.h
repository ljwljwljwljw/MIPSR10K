#pragma once

#include "common.h"
#include "module.h"
#include "issueUnit.h"
#include "BranchUnit.h"
#include "instruction.h"
#include "activelist.h"

class DecodeUnit : public Module {
public:
	int mapTable[REGISTER_SIZE];
	int busyBitTable[FREELIST_SIZE];
	int activeListNum;

	deque <Instruction> ins; //MAXSIZE == 8
	queue <int> freeList; //MAXSIZE == 64
	vector<ActiveList> activeList; //MAXSIZE == 32

	BranchUnit* bu;
	IssueUnit* iu;

	DecodeUnit(IssueUnit* input, BranchUnit* input_bu);
	~DecodeUnit();

	bool m_transmit(Instruction input);
	int  m_getFreeList();
	int* m_transmitBusyTable();
	void m_restoreStatus();

	//virtual functions from Module
	bool m_isClean();
	bool m_getEnable();
	void m_setNextEnable(bool result);
	void m_calc();
	void m_edge();
};