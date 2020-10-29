// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("味道[2;37;0m[2;37;0m", ({"vigina"}));        
        set("gender", "男性");                
        set("long", "好味道[2;37;0m
它是音盗的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "jhkk");
        set("owner_name", "音盗");
        set_temp("owner", "jhkk");
        set_temp("owner_name", "音盗");
        ::setup();
}
