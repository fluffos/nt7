// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("框框[2;37;0m[2;37;0m", ({"laohu"}));        
        set("gender", "男性");                
        set("long", "框框[2;37;0m
它是冷戾的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "lengli");
        set("owner_name", "冷戾");
        set_temp("owner", "lengli");
        set_temp("owner_name", "冷戾");
        ::setup();
}
