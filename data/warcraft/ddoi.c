// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("赤龙[2;37;0m[2;37;0m", ({"dragon_i"}));        
        set("gender", "男性");                
        set("long", "赤龙[2;37;0m
它是天偷的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ddoi");
        set("owner_name", "天偷");
        set_temp("owner", "ddoi");
        set_temp("owner_name", "天偷");
        ::setup();
}
