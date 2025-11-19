#include <fstream>
#include "MyApp.h"

using namespace std;

MyApp gMyApp;

BOOL MyApp::InitInstance() {
	ofstream fout("MFC Template.txt", ios_base::app);
	fout << "MFC Template\n";

	return EXIT_SUCCESS;
}