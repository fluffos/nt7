// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;36m眼[1;35m花[1;32m缭[1;31m乱[2;37;0m[2;37;0m[2;37;0m", ({"daze"}));        
        set("gender", "女性");                
        set("long", "眼花缭乱！[2;37;0m
它是冰雪飘渺的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "evilsnow");
        set("owner_name", "冰雪飘渺");
        set_temp("owner", "evilsnow");
        set_temp("owner_name", "冰雪飘渺");
        ::setup();
}
