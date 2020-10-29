// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("杜萱[2;37;0m[2;37;0m", ({"crystal"}));        
        set("gender", "女性");                
        set("long", "杜萱[2;37;0m
它是秦宝宝的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "sally");
        set("owner_name", "秦宝宝");
        set_temp("owner", "sally");
        set_temp("owner_name", "秦宝宝");
        ::setup();
}
