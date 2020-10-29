// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m云梦[2;37;0m[2;37;0m", ({"asd"}));        
        set("gender", "男性");                
        set("long", "云梦[2;37;0m
它是卢云的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yiko");
        set("owner_name", "卢云");
        set_temp("owner", "yiko");
        set_temp("owner_name", "卢云");
        ::setup();
}
