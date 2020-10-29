// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("士大夫[2;37;0m[2;37;0m", ({"wee"}));        
        set("gender", "男性");                
        set("long", "士大[2;37;0m
它是破颇的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "popo");
        set("owner_name", "破颇");
        set_temp("owner", "popo");
        set_temp("owner_name", "破颇");
        ::setup();
}
