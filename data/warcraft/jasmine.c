// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("东清龙[2;37;0m[2;37;0m", ({"eastdragon"}));        
        set("gender", "男性");                
        set("long", "这是四胜售的东清龙[2;37;0m
它是天蓝神魔的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "jasmine");
        set("owner_name", "天蓝神魔");
        set_temp("owner", "jasmine");
        set_temp("owner_name", "天蓝神魔");
        ::setup();
}
