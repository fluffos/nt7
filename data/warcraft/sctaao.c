// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白化小虎[2;37;0m[2;37;0m", ({"acooe"}));        
        set("gender", "男性");                
        set("long", "白化小虎[2;37;0m
它是于拘押的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "sctaao");
        set("owner_name", "于拘押");
        set_temp("owner", "sctaao");
        set_temp("owner_name", "于拘押");
        ::setup();
}
