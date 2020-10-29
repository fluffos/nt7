// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("云虎[2;37;0m[2;37;0m", ({"mycar"}));        
        set("gender", "男性");                
        set("long", "吴[2;37;0m
它是楚北云的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "zbdm");
        set("owner_name", "楚北云");
        set_temp("owner", "zbdm");
        set_temp("owner_name", "楚北云");
        ::setup();
}
