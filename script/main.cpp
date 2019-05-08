#include "../include/terminalDisplay.hpp"
#include "../include/shell.hpp"

using namespace std;

int main(){

    Shell(80, 25, "greg :~$ ").displayShell();

    return 0;
}
