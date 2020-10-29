// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("波多结衣子[2;37;0m[2;37;0m", ({"plg"}));        
        set("gender", "男性");                
        set("long", "@miaoshu[2;37;0m
它是立库六的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ltkf");
        set("owner_name", "立库六");
        set_temp("owner", "ltkf");
        set_temp("owner_name", "立库六");
        ::setup();
}
