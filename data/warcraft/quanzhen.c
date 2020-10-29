// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"long"}));        
        set("gender", "男性");                
        set("long", "  [2;37;0m
它是全真的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "quanzhen");
        set("owner_name", "全真");
        set_temp("owner", "quanzhen");
        set_temp("owner_name", "全真");
        ::setup();
}
