// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[33m土麒麟[2;37;0m[2;37;0m", ({"qmdamibb"}));        
        set("gender", "男性");                
        set("long", "$YEL$土麒麟[2;37;0m
它是王二的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "qmdamib");
        set("owner_name", "王二");
        set_temp("owner", "qmdamib");
        set_temp("owner_name", "王二");
        ::setup();
}
