// See <https://stackoverflow.com/questions/3360548/>

#ifdef _WIN32
#include <windows.h>

if (AttachConsole(ATTACH_PARENT_PROCESS)) {
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
}
#endif
