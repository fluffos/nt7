// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"nevalooy"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是叶凡尘的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "neval");
        set("owner_name", "叶凡尘");
        set_temp("owner", "neval");
        set_temp("owner_name", "叶凡尘");
        ::setup();
}
