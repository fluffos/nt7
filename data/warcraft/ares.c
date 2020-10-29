// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("无双[2;37;0m[2;37;0m", ({"bless"}));        
        set("gender", "男性");                
        set("long", "君临天下[2;37;0m
它是战神的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ares");
        set("owner_name", "战神");
        set_temp("owner", "ares");
        set_temp("owner_name", "战神");
        ::setup();
}
