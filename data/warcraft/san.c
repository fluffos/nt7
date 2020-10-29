// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火莲道人[2;37;0m[2;37;0m", ({"rodl"}));        
        set("gender", "男性");                
        set("long", "。。。。[2;37;0m
它是玉清的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "san");
        set("owner_name", "玉清");
        set_temp("owner", "san");
        set_temp("owner_name", "玉清");
        ::setup();
}
