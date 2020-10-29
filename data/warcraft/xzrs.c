// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("地图精[2;37;0m[2;37;0m", ({"maphere"}));        
        set("gender", "男性");                
        set("long", "23456[2;37;0m
它是坦克炮的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "xzrs");
        set("owner_name", "坦克炮");
        set_temp("owner", "xzrs");
        set_temp("owner_name", "坦克炮");
        ::setup();
}
