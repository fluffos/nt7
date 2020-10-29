// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m赤[1;33m麒麟[2;37;0m[2;37;0m", ({"rql"}));        
        set("gender", "男性");                
        set("long", "一片红色[2;37;0m
它是皓轩的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ljj");
        set("owner_name", "皓轩");
        set_temp("owner", "ljj");
        set_temp("owner_name", "皓轩");
        ::setup();
}
