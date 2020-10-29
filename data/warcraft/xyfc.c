// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("苍龙[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "女性");                
        set("long", "苍龙[2;37;0m
它是轩辕茗月的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xyfc");
        set("owner_name", "轩辕茗月");
        set_temp("owner", "xyfc");
        set_temp("owner_name", "轩辕茗月");
        ::setup();
}
