// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"ccww"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是学玩的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ccw");
        set("owner_name", "学玩");
        set_temp("owner", "ccw");
        set_temp("owner_name", "学玩");
        ::setup();
}
