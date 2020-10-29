// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"dsy"}));        
        set("gender", "男性");                
        set("long", "白虎[2;37;0m
它是菜农的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "wdpzd");
        set("owner_name", "菜农");
        set_temp("owner", "wdpzd");
        set_temp("owner_name", "菜农");
        ::setup();
}
