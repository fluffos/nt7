// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("檬[2;37;0m[2;37;0m", ({"kingslyb"}));        
        set("gender", "男性");                
        set("long", "檬[2;37;0m
它是收理的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "kingslya");
        set("owner_name", "收理");
        set_temp("owner", "kingslya");
        set_temp("owner_name", "收理");
        ::setup();
}
