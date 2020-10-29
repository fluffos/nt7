// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("先锋[2;37;0m[2;37;0m", ({"xiaodamii"}));        
        set("gender", "男性");                
        set("long", "先锋[2;37;0m
它是探路先锋的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xiaodami");
        set("owner_name", "探路先锋");
        set_temp("owner", "xiaodami");
        set_temp("owner_name", "探路先锋");
        ::setup();
}
