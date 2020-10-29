// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小青[2;37;0m[2;37;0m", ({"dsya"}));        
        set("gender", "男性");                
        set("long", "小青[2;37;0m
它是快刀小四的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "dsy");
        set("owner_name", "快刀小四");
        set_temp("owner", "dsy");
        set_temp("owner_name", "快刀小四");
        ::setup();
}
