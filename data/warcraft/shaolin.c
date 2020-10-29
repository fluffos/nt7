// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("中草药[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "中草药[2;37;0m
它是净段的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "shaolin");
        set("owner_name", "净段");
        set_temp("owner", "shaolin");
        set_temp("owner_name", "净段");
        ::setup();
}
