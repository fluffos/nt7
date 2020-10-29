// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[36m青龙[2;37;0m[2;37;0m", ({"qlong"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是邓邓的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ddeng");
        set("owner_name", "邓邓");
        set_temp("owner", "ddeng");
        set_temp("owner_name", "邓邓");
        ::setup();
}
