// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("雨琪[2;37;0m[2;37;0m", ({"yuqi"}));        
        set("gender", "女性");                
        set("long", "help nick[2;37;0m
它是雷禅的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "dio");
        set("owner_name", "雷禅");
        set_temp("owner", "dio");
        set_temp("owner_name", "雷禅");
        ::setup();
}
