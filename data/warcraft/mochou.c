// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m[1;31m独孤天摩[2;37;0m[2;37;0m", ({"skeg"}));        
        set("gender", "男性");                
        set("long", "独孤天摩[2;37;0m
它是莫愁的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "mochou");
        set("owner_name", "莫愁");
        set_temp("owner", "mochou");
        set_temp("owner_name", "莫愁");
        ::setup();
}
