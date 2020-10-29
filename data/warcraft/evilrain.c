// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;36m眼[1;31m花[1;33m缭[1;35m乱[2;37;0m[2;37;0m[2;37;0m", ({"daze"}));        
        set("gender", "女性");                
        set("long", "眼花缭乱！[2;37;0m
它是风雨飘渺的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "evilrain");
        set("owner_name", "风雨飘渺");
        set_temp("owner", "evilrain");
        set_temp("owner_name", "风雨飘渺");
        ::setup();
}
