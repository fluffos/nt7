// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m金[1;33m属[1;36m暴[1;32m龙[2;37;0m[2;37;0m", ({"goldlon"}));        
        set("gender", "男性");                
        set("long", "怎么都走步快[2;37;0m
它是东方流星的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "lonson");
        set("owner_name", "东方流星");
        set_temp("owner", "lonson");
        set_temp("owner_name", "东方流星");
        ::setup();
}
