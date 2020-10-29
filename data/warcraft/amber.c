// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m麒麟[2;37;0m[2;37;0m", ({"hupo"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是玄冥的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "amber");
        set("owner_name", "玄冥");
        set_temp("owner", "amber");
        set_temp("owner_name", "玄冥");
        ::setup();
}
