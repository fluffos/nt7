// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"shipet"}));        
        set("gender", "女性");                
        set("long", "麒麟[2;37;0m
它是石二的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "shib");
        set("owner_name", "石二");
        set_temp("owner", "shib");
        set_temp("owner_name", "石二");
        ::setup();
}
