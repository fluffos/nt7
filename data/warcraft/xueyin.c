// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m青龙[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是丨雪音丨的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xueyin");
        set("owner_name", "丨雪音丨");
        set_temp("owner", "xueyin");
        set_temp("owner_name", "丨雪音丨");
        ::setup();
}
