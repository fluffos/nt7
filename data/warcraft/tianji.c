// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m血麒麟[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "这是来自西藏的纯种藏獒。[2;37;0m
它是天机老人的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "tianji");
        set("owner_name", "天机老人");
        set_temp("owner", "tianji");
        set_temp("owner_name", "天机老人");
        ::setup();
}
