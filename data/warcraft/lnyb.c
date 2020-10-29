// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("二哥麒麟[2;37;0m[2;37;0m", ({"lnybride"}));        
        set("gender", "男性");                
        set("long", "二哥麒麟[2;37;0m
它是龙里二哥的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lnyb");
        set("owner_name", "龙里二哥");
        set_temp("owner", "lnyb");
        set_temp("owner_name", "龙里二哥");
        ::setup();
}
