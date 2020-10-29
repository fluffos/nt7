// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m青龙[2;37;0m[2;37;0m", ({"qlong"}));        
        set("gender", "男性");                
        set("long", "$HIW$青龙[2;37;0m
它是蓝精灵的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "smash");
        set("owner_name", "蓝精灵");
        set_temp("owner", "smash");
        set_temp("owner_name", "蓝精灵");
        ::setup();
}
