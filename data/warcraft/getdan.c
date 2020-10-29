// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("丹玉麒麟[2;37;0m[2;37;0m", ({"qudan"}));        
        set("gender", "男性");                
        set("long", "丹玉麒麟[2;37;0m
它是取丹的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "getdan");
        set("owner_name", "取丹");
        set_temp("owner", "getdan");
        set_temp("owner_name", "取丹");
        ::setup();
}
