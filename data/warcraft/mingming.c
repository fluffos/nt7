// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("命名[2;37;0m[2;37;0m", ({"min"}));        
        set("gender", "男性");                
        set("long", "命名[2;37;0m
它是明明的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "mingming");
        set("owner_name", "明明");
        set_temp("owner", "mingming");
        set_temp("owner_name", "明明");
        ::setup();
}
