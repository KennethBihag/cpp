#include "sharedspice.h"
#include <iostream>

using namespace std;

int my_ng_getchar(char* output, int id, void* userdata) {
	std::cout << "[OUTPUT]" << output << endl;
	return 0;
}

int my_ng_getstat(char* output, int id, void* userdata) {
	std::cout << "[STAT] " << output << std::endl;
	return 0;
}

int my_send_data(vecvaluesall* vva, int spv, int id, void* ptr) {
    for (int i = 0; i < vva->veccount; ++i) {
        auto &val = vva->vecsa[i];
        std::cout << "VecVal " << val->creal << " " << val->cimag << "i" << endl;
    }
    return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {
	cout << "SPICE Wrapper Running...\n";
	char *spcCmd = (char*)"plot";
	int ret = ngSpice_Init(my_ng_getchar, my_ng_getstat,0,my_send_data,0,0,0 );
    cout << endl;
    const char* circ[] = {
        "test",
        "V1 in 0 DC 5",
        "R1 in 0 1k",
        ".op",
        ".end"
    };
    const char* circ2[] = {
    "test2",
    "vV1 1 0 dc 0 ac 1 0",
    "+ distof1 0 0",
    "+ distof2 0 0",
    "+ sin(0 {3.5355 * 1.414213562} 5333.3333 0 0 0)",
    "cC1 0 3 1e-06",
    "rR1 2 3 1000 vresR1",
    ".model vresR1 r()",
    "dD1 1 2 1N4447__DIODE__1",
    ".MODEL 1N4447__DIODE__1  D(Is = 0.1p Rs = 4 CJO = 1p Tt = 12n Bv = 100 Ibv = 0.1p)",
    //".control",
    //"tran 1us 800us",
    //".endc",
    ".end"
    };

    ngSpice_Circ((char**)circ2);
    cout << endl;
    ngSpice_Command((char*)"tran 1us 800us");
    cout << endl;
    ngSpice_Command((char*)"print v(2,3)");


	return EXIT_SUCCESS;
}