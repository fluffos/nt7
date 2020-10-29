// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"yaoqqq"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是药球球的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yaoqq");
        set("owner_name", "药球球");
        set_temp("owner", "yaoqq");
        set_temp("owner_name", "药球球");
        ::setup();
}
