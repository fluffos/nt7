// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m财富宝[2;37;0m[2;37;0m", ({"cashsi"}));        
        set("gender", "男性");                
        set("long", "财富财富，劫贫济富！[2;37;0m
它是淘宝不肆的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "taobaosi");
        set("owner_name", "淘宝不肆");
        set_temp("owner", "taobaosi");
        set_temp("owner_name", "淘宝不肆");
        ::setup();
}
