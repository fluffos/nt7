// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("饕餮[2;37;0m[2;37;0m", ({"jinhu"}));        
        set("gender", "男性");                
        set("long", "饕餮[2;37;0m
它是紫河的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "king");
        set("owner_name", "紫河");
        set_temp("owner", "king");
        set_temp("owner_name", "紫河");
        ::setup();
}
