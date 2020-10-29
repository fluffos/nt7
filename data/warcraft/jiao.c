// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("又鸟[2;37;0m[2;37;0m", ({"mypet"}));        
        set("gender", "女性");                
        set("long", "又鸟[2;37;0m
它是李娇儿的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "jiao");
        set("owner_name", "李娇儿");
        set_temp("owner", "jiao");
        set_temp("owner_name", "李娇儿");
        ::setup();
}
