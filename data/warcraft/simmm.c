// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("龙[2;37;0m[2;37;0m", ({"long"}));        
        set("gender", "男性");                
        set("long", "龙[2;37;0m
它是踏雪无痕的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "simmm");
        set("owner_name", "踏雪无痕");
        set_temp("owner", "simmm");
        set_temp("owner_name", "踏雪无痕");
        ::setup();
}
