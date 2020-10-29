// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m雪豹[2;37;0m[2;37;0m", ({"nian"}));        
        set("gender", "男性");                
        set("long", "雪豹[2;37;0m
它是腿玩年的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "tuiwannian");
        set("owner_name", "腿玩年");
        set_temp("owner", "tuiwannian");
        set_temp("owner_name", "腿玩年");
        ::setup();
}
