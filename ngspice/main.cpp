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
        std::cout << val->creal << "; ";
    }
    cout << endl;
    return EXIT_SUCCESS;
}

int my_send_init(vecinfoall* via, int id, void* ptr) {
    cout << "my_send_init:\nName; Type; Count;\n";
    for (int i = 0; i < via->veccount; ++i) {
        auto &v = via->vecs[i];
        vector_info &vi = *ngGet_Vec_Info(v->vecname);
        cout << vi.v_name << "; " << vi.v_type << "; " << vi.v_length << "\n";
    }
    return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {
	cout << "SPICE Wrapper Running...\n";
	char *spcCmd = (char*)"plot";
    void *myObj = spcCmd;
	int ret = ngSpice_Init(my_ng_getchar, my_ng_getstat,0,my_send_data,my_send_init,0, myObj);
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
    auto printVecs = [&](){
        auto currPlot = ngSpice_CurPlot();
        auto allVecs = ngSpice_AllVecs(currPlot);
        cout << "Vectors: ";
        while (true) {
            cout << *allVecs << ";";
            ++allVecs;
            if (!*allVecs)
                break;
        }
        cout << endl;
    };
    cout << "Before sim\n";
    printVecs();
    ngSpice_Command((char*)"tran 1us 800us");
    cout << "After sim\n";
    printVecs();
    cout << endl;
    //ngSpice_Command((char*)"print v(2,3)");
	return EXIT_SUCCESS;
}