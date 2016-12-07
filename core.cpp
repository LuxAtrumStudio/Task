#include "induco.h"
#include "task.h"
#include <ctime>
#include <iostream>
#include <math.h>
#include <pessum.h>

int main() {
  pessum::InitializePessumComponents();
  task::MainLoop();
  pessum::TerminatePessumComponents();
}
