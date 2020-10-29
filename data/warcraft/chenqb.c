// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("玄武[2;37;0m[2;37;0m", ({"eeee"}));        
        set("gender", "男性");                
        set("long", "玄武[2;37;0m
它是成空的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "chenqb");
        set("owner_name", "成空");
        set_temp("owner", "chenqb");
        set_temp("owner_name", "成空");
        ::setup();
}
