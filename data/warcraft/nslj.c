// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("地图精[2;37;0m[2;37;0m", ({"maphere"}));        
        set("gender", "男性");                
        set("long", "23456[2;37;0m
它是无所谓的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "nslj");
        set("owner_name", "无所谓");
        set_temp("owner", "nslj");
        set_temp("owner_name", "无所谓");
        ::setup();
}
