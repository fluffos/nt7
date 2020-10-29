// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"qinlin"}));        
        set("gender", "女性");                
        set("long", "麒麟[2;37;0m
它是端木海的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "jyfsc");
        set("owner_name", "端木海");
        set_temp("owner", "jyfsc");
        set_temp("owner_name", "端木海");
        ::setup();
}
