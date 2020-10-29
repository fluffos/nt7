// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[30m青龙[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是乌当贰的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "warrierg");
        set("owner_name", "乌当贰");
        set_temp("owner", "warrierg");
        set_temp("owner_name", "乌当贰");
        ::setup();
}
