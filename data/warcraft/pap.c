// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("和你[2;37;0m[2;37;0m", ({"paps"}));        
        set("gender", "男性");                
        set("long", "和你[2;37;0m
它是的杀的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "pap");
        set("owner_name", "的杀");
        set_temp("owner", "pap");
        set_temp("owner_name", "的杀");
        ::setup();
}
