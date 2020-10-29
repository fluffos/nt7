// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m木乙[2;37;0m[2;37;0m", ({"matbpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是乙木的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "matb");
        set("owner_name", "乙木");
        set_temp("owner", "matb");
        set_temp("owner_name", "乙木");
        ::setup();
}
