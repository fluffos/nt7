// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("脏麒麟[2;37;0m[2;37;0m", ({"jql"}));        
        set("gender", "男性");                
        set("long", "脏麒麟[2;37;0m
它是拾荒折的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "jqd");
        set("owner_name", "拾荒折");
        set_temp("owner", "jqd");
        set_temp("owner_name", "拾荒折");
        ::setup();
}
