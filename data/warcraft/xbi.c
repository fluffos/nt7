// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("地图精[2;37;0m[2;37;0m", ({"maphere"}));        
        set("gender", "男性");                
        set("long", "23124fe[2;37;0m
它是小兵辛的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xbi");
        set("owner_name", "小兵辛");
        set_temp("owner", "xbi");
        set_temp("owner_name", "小兵辛");
        ::setup();
}
