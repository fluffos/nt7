// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("彩云[2;37;0m[2;37;0m", ({"judy"}));        
        set("gender", "女性");                
        set("long", "无[2;37;0m
它是云依的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "rty");
        set("owner_name", "云依");
        set_temp("owner", "rty");
        set_temp("owner_name", "云依");
        ::setup();
}
