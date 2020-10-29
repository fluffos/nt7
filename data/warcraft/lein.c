// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("马[2;37;0m[2;37;0m", ({"hell"}));        
        set("gender", "男性");                
        set("long", "坐骑[2;37;0m
它是雪姐夫的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lein");
        set("owner_name", "雪姐夫");
        set_temp("owner", "lein");
        set_temp("owner_name", "雪姐夫");
        ::setup();
}
