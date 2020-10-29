// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("烦烦烦[2;37;0m[2;37;0m", ({"yaofff"}));        
        set("gender", "男性");                
        set("long", "烦烦烦[2;37;0m
它是药发发的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yaoff");
        set("owner_name", "药发发");
        set_temp("owner", "yaoff");
        set_temp("owner_name", "药发发");
        ::setup();
}
