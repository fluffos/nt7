// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;36m云[2;37;0m[1;31m起[1;32m龙[1;35m骧[2;37;0m[2;37;0m", ({"cloudy"}));        
        set("gender", "男性");                
        set("long", "云起龙骧[2;37;0m
它是云飘飘的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "cloud");
        set("owner_name", "云飘飘");
        set_temp("owner", "cloud");
        set_temp("owner_name", "云飘飘");
        ::setup();
}
