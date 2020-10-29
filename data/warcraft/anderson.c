// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("火车[2;37;0m[2;37;0m", ({"uub"}));        
        set("gender", "男性");                
        set("long", "火车[2;37;0m
它是可爱薯条的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "anderson");
        set("owner_name", "可爱薯条");
        set_temp("owner", "anderson");
        set_temp("owner_name", "可爱薯条");
        ::setup();
}
