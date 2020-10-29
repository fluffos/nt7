// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白狐[2;37;0m[2;37;0m", ({"baihu"}));        
        set("gender", "男性");                
        set("long", "白[2;37;0m
它是风月无边的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "fengyue");
        set("owner_name", "风月无边");
        set_temp("owner", "fengyue");
        set_temp("owner_name", "风月无边");
        ::setup();
}
