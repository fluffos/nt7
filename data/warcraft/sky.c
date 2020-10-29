// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m小白龙[2;37;0m[2;37;0m", ({"shou"}));        
        set("gender", "女性");                
        set("long", "             [2;37;0m
它是西施的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "sky");
        set("owner_name", "西施");
        set_temp("owner", "sky");
        set_temp("owner_name", "西施");
        ::setup();
}
