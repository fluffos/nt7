// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("玄武[2;37;0m[2;37;0m", ({"goo"}));        
        set("gender", "男性");                
        set("long", "玄武[2;37;0m
它是心已伤的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "chenf");
        set("owner_name", "心已伤");
        set_temp("owner", "chenf");
        set_temp("owner_name", "心已伤");
        ::setup();
}
