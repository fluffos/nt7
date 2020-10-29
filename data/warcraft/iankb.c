// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("一天[2;37;0m[2;37;0m", ({"choose"}));        
        set("gender", "女性");                
        set("long", "look[2;37;0m
它是一风的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "iankb");
        set("owner_name", "一风");
        set_temp("owner", "iankb");
        set_temp("owner_name", "一风");
        ::setup();
}
