// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"qingvii"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是菜农八的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "cnh");
        set("owner_name", "菜农八");
        set_temp("owner", "cnh");
        set_temp("owner_name", "菜农八");
        ::setup();
}
