// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("云淡风轻[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "如风如云快跑奔驰的麒麟[2;37;0m
它是马成的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "matlab");
        set("owner_name", "马成");
        set_temp("owner", "matlab");
        set_temp("owner_name", "马成");
        ::setup();
}
