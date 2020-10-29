// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;32m小[1;31m麒[1;33m麟[2;37;0m[2;37;0m", ({"lql"}));        
        set("gender", "女性");                
        set("long", "一只小麒麟[2;37;0m
它是做药的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ltd");
        set("owner_name", "做药");
        set_temp("owner", "ltd");
        set_temp("owner_name", "做药");
        ::setup();
}
