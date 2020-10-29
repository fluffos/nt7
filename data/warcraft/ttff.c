// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m小涯[2;37;0m[2;37;0m", ({"ttffa"}));        
        set("gender", "男性");                
        set("long", "伴生小兽，永远相随。[2;37;0m
它是博昱的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ttff");
        set("owner_name", "博昱");
        set_temp("owner", "ttff");
        set_temp("owner_name", "博昱");
        ::setup();
}
