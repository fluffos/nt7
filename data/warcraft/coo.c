// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m电毛驴[2;37;0m[2;37;0m", ({"coolong"}));        
        set("gender", "男性");                
        set("long", "$HIY$电毛驴[2;37;0m
它是袭风的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "coo");
        set("owner_name", "袭风");
        set_temp("owner", "coo");
        set_temp("owner_name", "袭风");
        ::setup();
}
