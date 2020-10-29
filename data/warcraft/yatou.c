// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m丫米[2;37;0m[2;37;0m", ({"yami"}));        
        set("gender", "男性");                
        set("long", "$HIR$丫米[2;37;0m
它是丫头的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yatou");
        set("owner_name", "丫头");
        set_temp("owner", "yatou");
        set_temp("owner_name", "丫头");
        ::setup();
}
