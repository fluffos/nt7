// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"carofheyue"}));        
        set("gender", "男性");                
        set("long", "heyue的魔幻兽[2;37;0m
它是北宫荷月的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "heyue");
        set("owner_name", "北宫荷月");
        set_temp("owner", "heyue");
        set_temp("owner_name", "北宫荷月");
        ::setup();
}
