using namespace std;

#include "Automato.h"

int main_old(int argc, char **argv) {
	//TODO: Getopts
	//TODO: Timeout

	Automato a;
	a.lerDefinicao();
	cout << a.calcularPalavraSincronizadora() << endl;

	return 0;
}
