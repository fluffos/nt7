// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"xyzabc"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是三四的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "abcxyz");
        set("owner_name", "三四");
        set_temp("owner", "abcxyz");
        set_temp("owner_name", "三四");
        ::setup();
}
