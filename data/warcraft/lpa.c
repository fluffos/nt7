// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m[44;1m老爬啊[2;37;0m[2;37;0m", ({"lpas"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是老怕的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lpa");
        set("owner_name", "老怕");
        set_temp("owner", "lpa");
        set_temp("owner_name", "老怕");
        ::setup();
}
