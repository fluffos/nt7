// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("龙[2;37;0m[2;37;0m", ({"long"}));        
        set("gender", "男性");                
        set("long", "龙[2;37;0m
它是护腕师傅的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "iwrists");
        set("owner_name", "护腕师傅");
        set_temp("owner", "iwrists");
        set_temp("owner_name", "护腕师傅");
        ::setup();
}
