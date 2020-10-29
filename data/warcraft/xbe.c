// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("地图精[2;37;0m[2;37;0m", ({"maphere"}));        
        set("gender", "女性");                
        set("long", "1341324[2;37;0m
它是小兵戊的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "xbe");
        set("owner_name", "小兵戊");
        set_temp("owner", "xbe");
        set_temp("owner_name", "小兵戊");
        ::setup();
}
