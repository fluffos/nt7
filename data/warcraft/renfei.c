// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("任飞麒麟[2;37;0m[2;37;0m", ({"renfeiride"}));        
        set("gender", "男性");                
        set("long", "任飞麒麟[2;37;0m
它是任正飞的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "renfei");
        set("owner_name", "任正飞");
        set_temp("owner", "renfei");
        set_temp("owner_name", "任正飞");
        ::setup();
}
