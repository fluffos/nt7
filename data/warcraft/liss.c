// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m师师[2;37;0m[2;37;0m", ({"lisss"}));        
        set("gender", "男性");                
        set("long", "呵呵[2;37;0m
它是李师师的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "liss");
        set("owner_name", "李师师");
        set_temp("owner", "liss");
        set_temp("owner_name", "李师师");
        ::setup();
}
