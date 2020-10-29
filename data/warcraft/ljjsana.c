// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("快跑[2;37;0m[2;37;0m", ({"pdk"}));        
        set("gender", "男性");                
        set("long", "快跑[2;37;0m
它是散人的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ljjsana");
        set("owner_name", "散人");
        set_temp("owner", "ljjsana");
        set_temp("owner_name", "散人");
        ::setup();
}
