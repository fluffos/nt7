// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("地图精[2;37;0m[2;37;0m", ({"maphere"}));        
        set("gender", "男性");                
        set("long", "1111[2;37;0m
它是宇宙的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "nslg");
        set("owner_name", "宇宙");
        set_temp("owner", "nslg");
        set_temp("owner_name", "宇宙");
        ::setup();
}
