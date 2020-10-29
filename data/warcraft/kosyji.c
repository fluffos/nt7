// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m玖研[2;37;0m[2;37;0m", ({"kosyjipet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是研玖的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kosyji");
        set("owner_name", "研玖");
        set_temp("owner", "kosyji");
        set_temp("owner_name", "研玖");
        ::setup();
}
