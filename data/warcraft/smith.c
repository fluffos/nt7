// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m风[1;35m狼[2;37;0m[2;37;0m[2;37;0m", ({"wsmith"}));        
        set("gender", "女性");                
        set("long", "风狼[2;37;0m
它是擎云的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "smith");
        set("owner_name", "擎云");
        set_temp("owner", "smith");
        set_temp("owner_name", "擎云");
        ::setup();
}
