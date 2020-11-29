#include "pch.h"

int main(int argc, char* argv[])
{
   [[maybe_unused]] const size_t x = 2ull * 1024ull * 1024ull * 1024ull;
   cout << x << '\n';

   const int zenUnitExitCode = ZenUnit::RunTests(argc, argv);
   return zenUnitExitCode;
}
