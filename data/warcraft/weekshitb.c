// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("异形[2;37;0m[2;37;0m", ({"dna"}));        
        set("gender", "男性");                
        set("long", "逆种[2;37;0m
它是女人的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "weekshitb");
        set("owner_name", "女人");
        set_temp("owner", "weekshitb");
        set_temp("owner_name", "女人");
        ::setup();
}
