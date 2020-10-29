// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("无风龙[2;37;0m[2;37;0m", ({"wufeng"}));        
        set("gender", "男性");                
        set("long", "无风龙[2;37;0m
它是魔无风的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "mwf");
        set("owner_name", "魔无风");
        set_temp("owner", "mwf");
        set_temp("owner_name", "魔无风");
        ::setup();
}
