// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("无电[2;37;0m[2;37;0m", ({"wudian"}));        
        set("gender", "男性");                
        set("long", "无电[2;37;0m
它是魔无电的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "mwd");
        set("owner_name", "魔无电");
        set_temp("owner", "mwd");
        set_temp("owner_name", "魔无电");
        ::setup();
}
