// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"fkee"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是福鄂的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "fke");
        set("owner_name", "福鄂");
        set_temp("owner", "fke");
        set_temp("owner_name", "福鄂");
        ::setup();
}
