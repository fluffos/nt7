// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m玉麒麟[2;37;0m[2;37;0m", ({"yql"}));        
        set("gender", "男性");                
        set("long", "上古神兽[2;37;0m
它是散仙的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "maya");
        set("owner_name", "散仙");
        set_temp("owner", "maya");
        set_temp("owner_name", "散仙");
        ::setup();
}
