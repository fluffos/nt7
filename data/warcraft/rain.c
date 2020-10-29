// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m闪电[2;37;0m[2;37;0m", ({"rainbow"}));        
        set("gender", "男性");                
        set("long", "一只黑色高又冷漠的战龙[2;37;0m
它是夏雨的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "rain");
        set("owner_name", "夏雨");
        set_temp("owner", "rain");
        set_temp("owner_name", "夏雨");
        ::setup();
}
