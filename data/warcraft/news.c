// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("付款[2;37;0m[2;37;0m", ({"oko"}));        
        set("gender", "男性");                
        set("long", "了[2;37;0m
它是新新的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "news");
        set("owner_name", "新新");
        set_temp("owner", "news");
        set_temp("owner_name", "新新");
        ::setup();
}
