// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("神仙龙[2;37;0m[2;37;0m", ({"shengou"}));        
        set("gender", "男性");                
        set("long", "神仙龙[2;37;0m
它是雷锋的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "leifeng");
        set("owner_name", "雷锋");
        set_temp("owner", "leifeng");
        set_temp("owner_name", "雷锋");
        ::setup();
}
