// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("颜色[2;37;0m[2;37;0m", ({"idid"}));        
        set("gender", "男性");                
        set("long", "颜色[2;37;0m
它是回车的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xtest");
        set("owner_name", "回车");
        set_temp("owner", "xtest");
        set_temp("owner_name", "回车");
        ::setup();
}
