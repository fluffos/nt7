// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("龙大[2;37;0m[2;37;0m", ({"longda"}));        
        set("gender", "男性");                
        set("long", "威猛[2;37;0m
它是长大安的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "changanwd");
        set("owner_name", "长大安");
        set_temp("owner", "changanwd");
        set_temp("owner_name", "长大安");
        ::setup();
}
