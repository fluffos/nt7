// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("水滴[2;37;0m[2;37;0m", ({"shuidi"}));        
        set("gender", "男性");                
        set("long", "水滴[2;37;0m
它是暴雨的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "baoyu");
        set("owner_name", "暴雨");
        set_temp("owner", "baoyu");
        set_temp("owner_name", "暴雨");
        ::setup();
}
