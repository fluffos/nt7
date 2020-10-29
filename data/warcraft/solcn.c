// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;35m世京[2;37;0m[2;37;0m", ({"solcngo"}));        
        set("gender", "男性");                
        set("long", "$BLINK$$HIM$世京[2;37;0m
它是有名有姓的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "solcn");
        set("owner_name", "有名有姓");
        set_temp("owner", "solcn");
        set_temp("owner_name", "有名有姓");
        ::setup();
}
