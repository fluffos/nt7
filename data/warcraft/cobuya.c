// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("色虎[2;37;0m[2;37;0m", ({"laohu"}));        
        set("gender", "男性");                
        set("long", "一只色色的老虎[2;37;0m
它是紫色的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "cobuya");
        set("owner_name", "紫色");
        set_temp("owner", "cobuya");
        set_temp("owner_name", "紫色");
        ::setup();
}
