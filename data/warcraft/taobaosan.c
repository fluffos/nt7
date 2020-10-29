// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m现金宝[2;37;0m[2;37;0m", ({"coinsan"}));        
        set("gender", "男性");                
        set("long", "现金为王，王道现金！[2;37;0m
它是淘宝小叁的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "taobaosan");
        set("owner_name", "淘宝小叁");
        set_temp("owner", "taobaosan");
        set_temp("owner_name", "淘宝小叁");
        ::setup();
}
