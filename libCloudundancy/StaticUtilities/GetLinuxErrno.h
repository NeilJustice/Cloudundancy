#pragma once

#if defined __linux__ || defined __APPLE__
int* GetLinuxErrno();
#endif

