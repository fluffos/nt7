// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m天外飞龙[2;37;0m[2;37;0m", ({"llong"}));        
        set("gender", "男性");                
        set("long", "天外飞龙[2;37;0m
它是飞翔的鱼的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wxbln");
        set("owner_name", "飞翔的鱼");
        set_temp("owner", "wxbln");
        set_temp("owner_name", "飞翔的鱼");
        ::setup();
}
