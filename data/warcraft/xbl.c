// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("地图精[2;37;0m[2;37;0m", ({"maphere"}));        
        set("gender", "男性");                
        set("long", "ade[2;37;0m
它是小兵葵的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "xbl");
        set("owner_name", "小兵葵");
        set_temp("owner", "xbl");
        set_temp("owner_name", "小兵葵");
        ::setup();
}
