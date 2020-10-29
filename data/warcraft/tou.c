// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("虫子[2;37;0m[2;37;0m", ({"chong"}));        
        set("gender", "男性");                
        set("long", "虫子[2;37;0m
它是木头的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "tou");
        set("owner_name", "木头");
        set_temp("owner", "tou");
        set_temp("owner_name", "木头");
        ::setup();
}
