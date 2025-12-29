#include "testlib.h"
using namespace std;
int main(int argc, char **argv) {
  registerTestlibCmd(argc, argv);
  long realdiam = ans.readInt(), canddiam = ouf.readInt();
  if ((realdiam == -1 && canddiam != -1) || 
        (realdiam != -1 && canddiam != realdiam && canddiam != realdiam + 1))
            quitf(_wa,"incorrect answer\n");
    quitf(_ok,"OK, accept\n");
}
