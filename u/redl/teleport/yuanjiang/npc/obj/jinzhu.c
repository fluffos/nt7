// This program is a part of NITAN MudLIB 
// redl 2015/10
#include <ansi.h> 
inherit ITEM;

void create()
{
        set_name(NOR YEL "金蛛" NOR, ({"jin zhu", "jin", "zhu" }));
                set("long", "这是只休眠着的异种生物，驱使方法可能要去哀牢山问大颠上人了。\n");
                set("unit", "只");
                set("value", 10000000);
                set("base_value", 10000000);
                set("base_unit", "只");
                set("base_weight", 1000000);
                set("is jin zhu", 1);
        setup();
}

