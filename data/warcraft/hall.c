// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m金毛吼[2;37;0m[2;37;0m", ({"doo"}));        
        set("gender", "男性");                
        set("long", "坐骑[2;37;0m
它是若示的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "hall");
        set("owner_name", "若示");
        set_temp("owner", "hall");
        set_temp("owner_name", "若示");
        ::setup();
}
