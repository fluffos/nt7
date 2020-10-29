// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m玉蛟龙[2;37;0m[2;37;0m", ({"gyxds"}));        
        set("gender", "男性");                
        set("long", "浮云神马，所向无敌[2;37;0m
它是顾玉侠的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "gyx");
        set("owner_name", "顾玉侠");
        set_temp("owner", "gyx");
        set_temp("owner_name", "顾玉侠");
        ::setup();
}
