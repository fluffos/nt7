// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m龟龟[2;37;0m[2;37;0m", ({"asd"}));        
        set("gender", "男性");                
        set("long", "$HIG$龟龟[2;37;0m
它是四道风的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "sdf");
        set("owner_name", "四道风");
        set_temp("owner", "sdf");
        set_temp("owner_name", "四道风");
        ::setup();
}
