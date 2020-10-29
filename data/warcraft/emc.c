// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("郭大襄[2;37;0m[2;37;0m", ({"emclong"}));        
        set("gender", "男性");                
        set("long", "俘哦地[2;37;0m
它是祖师看着的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "emc");
        set("owner_name", "祖师看着");
        set_temp("owner", "emc");
        set_temp("owner_name", "祖师看着");
        ::setup();
}
