// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老幺[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "老幺[2;37;0m
它是魔虎的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "uuu");
        set("owner_name", "魔虎");
        set_temp("owner", "uuu");
        set_temp("owner_name", "魔虎");
        ::setup();
}
