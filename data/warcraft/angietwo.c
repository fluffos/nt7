// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("安琪[2;37;0m[2;37;0m", ({"angie"}));        
        set("gender", "男性");                
        set("long", "快乐的小安琪[2;37;0m
它是小菜刀的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "angietwo");
        set("owner_name", "小菜刀");
        set_temp("owner", "angietwo");
        set_temp("owner_name", "小菜刀");
        ::setup();
}
