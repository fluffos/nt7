// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;37m冰[2;37;0m[1;34m天[5m[1;37m雪[2;37;0m[1;33m地[2;37;0m[2;37;0m", ({"icesnow"}));        
        set("gender", "男性");                
        set("long", "冰天雪地！[2;37;0m
它是冰雪飘零的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "evilice");
        set("owner_name", "冰雪飘零");
        set_temp("owner", "evilice");
        set_temp("owner_name", "冰雪飘零");
        ::setup();
}
