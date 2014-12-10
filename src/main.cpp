#include "common.h"
#include "instruction.h"
#include "fetchUnit.h"
#include "decodeUnit.h"
#include "issueUnit.h"
#include "executionUnit.h"

void startPipeline(FetchUnit* fu, DecodeUnit* du, IssueUnit* iu) {
	while(1) {
		fu->m_calc();
		du->m_calc();
		iu->m_calc();

		iu->m_edge();
		du->m_edge();
		fu->m_edge();
		
		if(fu->m_isClean() && du->m_isClean() && iu->m_isClean()) { //work is done
			
			break;
		}
	}

}


int main(int argc, char* argv[]) {
	if(argc <= 1) {
		cout<<"Please insert tracefile.txt"<<endl;

		return 0;
	}

	ifstream traceFile;
	string input = "";

	ExecutionUnit exeUnit;
	IssueUnit issueUnit(&exeUnit);
	DecodeUnit decodeUnit(&issueUnit);
	FetchUnit fetchUnit(&decodeUnit);
	int insId = 0;
	
	traceFile.open(argv[1]);

	while(getline(traceFile, input)) {
		Instruction insFromFile(input, insId);
		insFromFile.m_printIns();

		fetchUnit.pushInstructions(insFromFile);
		insId++;
	}

	startPipeline(&fetchUnit, &decodeUnit, &issueUnit);

	return 0;
}



