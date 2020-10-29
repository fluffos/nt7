// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("龙龙[2;37;0m[2;37;0m", ({"qlong"}));        
        set("gender", "男性");                
        set("long", "龙龙[2;37;0m
它是笨笨的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "thinkday");
        set("owner_name", "笨笨");
        set_temp("owner", "thinkday");
        set_temp("owner_name", "笨笨");
        ::setup();
}
