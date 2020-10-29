// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("地图精[2;37;0m[2;37;0m", ({"maphere"}));        
        set("gender", "女性");                
        set("long", "111[2;37;0m
它是橙子的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "orga");
        set("owner_name", "橙子");
        set_temp("owner", "orga");
        set_temp("owner_name", "橙子");
        ::setup();
}
