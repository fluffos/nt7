// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m远古龙[2;37;0m[2;37;0m", ({"konglong"}));        
        set("gender", "男性");                
        set("long", "$RED$远古龙[2;37;0m
它是重小雨的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "woacsy");
        set("owner_name", "重小雨");
        set_temp("owner", "woacsy");
        set_temp("owner_name", "重小雨");
        ::setup();
}
