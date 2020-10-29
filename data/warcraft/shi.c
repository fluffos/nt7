// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"shipet"}));        
        set("gender", "女性");                
        set("long", "麒麟[2;37;0m
它是石头的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "shi");
        set("owner_name", "石头");
        set_temp("owner", "shi");
        set_temp("owner_name", "石头");
        ::setup();
}
