// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小飞侠[2;37;0m[2;37;0m", ({"apple"}));        
        set("gender", "男性");                
        set("long", "常回家看看[2;37;0m
它是菜鸟的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "cainiao");
        set("owner_name", "菜鸟");
        set_temp("owner", "cainiao");
        set_temp("owner_name", "菜鸟");
        ::setup();
}
