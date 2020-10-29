// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("米多多兽[2;37;0m[2;37;0m", ({"miduoshou"}));        
        set("gender", "男性");                
        set("long", "米多多兽[2;37;0m
它是米多气的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "miduoling");
        set("owner_name", "米多气");
        set_temp("owner", "miduoling");
        set_temp("owner_name", "米多气");
        ::setup();
}
