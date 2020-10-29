// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"yaozzz"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是药制作的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yaozz");
        set("owner_name", "药制作");
        set_temp("owner", "yaozz");
        set_temp("owner_name", "药制作");
        ::setup();
}
