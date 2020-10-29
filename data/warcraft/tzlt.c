// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m东方金龙[2;37;0m[2;37;0m", ({"dragonraja"}));        
        set("gender", "男性");                
        set("long", "一只金光灿灿的神龙，浑身散发古老神秘的气息。[2;37;0m
它是魔神的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "tzlt");
        set("owner_name", "魔神");
        set_temp("owner", "tzlt");
        set_temp("owner_name", "魔神");
        ::setup();
}
