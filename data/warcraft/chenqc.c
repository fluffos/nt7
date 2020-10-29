// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("玄武[2;37;0m[2;37;0m", ({"uuuu"}));        
        set("gender", "男性");                
        set("long", "玄武[2;37;0m
它是成了的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "chenqc");
        set("owner_name", "成了");
        set_temp("owner", "chenqc");
        set_temp("owner_name", "成了");
        ::setup();
}
