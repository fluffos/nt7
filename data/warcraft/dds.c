// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[33m麒麟[2;37;0m[2;37;0m", ({"ffire"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是慕容绝的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "dds");
        set("owner_name", "慕容绝");
        set_temp("owner", "dds");
        set_temp("owner_name", "慕容绝");
        ::setup();
}
