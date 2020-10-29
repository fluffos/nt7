// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m墨麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "墨麒麟[2;37;0m
它是劫云的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "sleme");
        set("owner_name", "劫云");
        set_temp("owner", "sleme");
        set_temp("owner_name", "劫云");
        ::setup();
}
