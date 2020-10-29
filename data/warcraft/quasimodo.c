// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"carofquasimodo"}));        
        set("gender", "男性");                
        set("long", "Quasimodo的魔幻兽[2;37;0m
它是伽西莫多的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "quasimodo");
        set("owner_name", "伽西莫多");
        set_temp("owner", "quasimodo");
        set_temp("owner_name", "伽西莫多");
        ::setup();
}
