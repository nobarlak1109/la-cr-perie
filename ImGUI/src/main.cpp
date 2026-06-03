#include "View.h"
int main(int, char**)
{
    View view;

    if(!view.Init())
        return 1;

    view.Run();
    view.Shutdown();

    return 0;
}