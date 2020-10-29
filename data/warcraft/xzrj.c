// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("地图精[2;37;0m[2;37;0m", ({"maphere"}));        
        set("gender", "男性");                
        set("long", "23456[2;37;0m
它是出云辰龙的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "xzrj");
        set("owner_name", "出云辰龙");
        set_temp("owner", "xzrj");
        set_temp("owner_name", "出云辰龙");
        ::setup();
}
