// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[33m土麒麟[2;37;0m[2;37;0m", ({"qmdamidd"}));        
        set("gender", "男性");                
        set("long", "$YEL$土麒麟[2;37;0m
它是王四的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "qmdamid");
        set("owner_name", "王四");
        set_temp("owner", "qmdamid");
        set_temp("owner_name", "王四");
        ::setup();
}
