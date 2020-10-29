// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("地图精[2;37;0m[2;37;0m", ({"maphere"}));        
        set("gender", "男性");                
        set("long", "23456[2;37;0m
它是三角翼的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "xzrt");
        set("owner_name", "三角翼");
        set_temp("owner", "xzrt");
        set_temp("owner_name", "三角翼");
        ::setup();
}
