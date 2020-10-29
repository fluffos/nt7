// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m青龙[2;37;0m[2;37;0m", ({"dragon"}));        
        set("gender", "男性");                
        set("long", "。。。。[2;37;0m
它是明玉的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "mingyu");
        set("owner_name", "明玉");
        set_temp("owner", "mingyu");
        set_temp("owner_name", "明玉");
        ::setup();
}
