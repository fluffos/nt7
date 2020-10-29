// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("地图精[2;37;0m[2;37;0m", ({"maphere"}));        
        set("gender", "男性");                
        set("long", "12323[2;37;0m
它是小兵己的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "xbf");
        set("owner_name", "小兵己");
        set_temp("owner", "xbf");
        set_temp("owner_name", "小兵己");
        ::setup();
}
