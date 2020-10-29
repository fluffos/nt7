// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("跑车[2;37;0m[2;37;0m", ({"gtr"}));        
        set("gender", "男性");                
        set("long", "跑车[2;37;0m
它是破不破的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "pop");
        set("owner_name", "破不破");
        set_temp("owner", "pop");
        set_temp("owner_name", "破不破");
        ::setup();
}
