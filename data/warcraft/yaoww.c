// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"yaowww"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是药不溜的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yaoww");
        set("owner_name", "药不溜");
        set_temp("owner", "yaoww");
        set_temp("owner_name", "药不溜");
        ::setup();
}
