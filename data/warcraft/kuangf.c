// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("泥鳅[2;37;0m[2;37;0m", ({"along"}));        
        set("gender", "男性");                
        set("long", "灰白[2;37;0m
它是狂六的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kuangf");
        set("owner_name", "狂六");
        set_temp("owner", "kuangf");
        set_temp("owner_name", "狂六");
        ::setup();
}
