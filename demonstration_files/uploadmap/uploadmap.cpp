#define F_CPU 8000000
#include "cartographie/map.h"

int main()
{

    Map map;
    map.upload_map();
    _delay_ms(1000);
    map.read_map();
}