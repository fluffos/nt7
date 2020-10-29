// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("魔幻一[2;37;0m[2;37;0m", ({"mohuana"}));        
        set("gender", "男性");                
        set("long", "魔幻一[2;37;0m
它是神器仓一的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "shenqia");
        set("owner_name", "神器仓一");
        set_temp("owner", "shenqia");
        set_temp("owner_name", "神器仓一");
        ::setup();
}
