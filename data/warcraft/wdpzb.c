// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"dsy"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是菩丹贰的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "wdpzb");
        set("owner_name", "菩丹贰");
        set_temp("owner", "wdpzb");
        set_temp("owner_name", "菩丹贰");
        ::setup();
}
