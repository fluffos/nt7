// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("地图精[2;37;0m[2;37;0m", ({"maphere"}));        
        set("gender", "男性");                
        set("long", "12324[2;37;0m
它是小兵乙的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "xbb");
        set("owner_name", "小兵乙");
        set_temp("owner", "xbb");
        set_temp("owner_name", "小兵乙");
        ::setup();
}
