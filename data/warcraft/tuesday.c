// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m一[1;31m日[5m[1;31m[1;36m二天[2;37;0m[2;37;0m[2;37;0m", ({"tue"}));        
        set("gender", "女性");                
        set("long", "^@@^![2;37;0m
它是星期二的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "tuesday");
        set("owner_name", "星期二");
        set_temp("owner", "tuesday");
        set_temp("owner_name", "星期二");
        ::setup();
}
