// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[33m土麒麟[2;37;0m[2;37;0m", ({"qmdamicc"}));        
        set("gender", "男性");                
        set("long", "wartime[2;37;0m
它是王三的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "qmdamic");
        set("owner_name", "王三");
        set_temp("owner", "qmdamic");
        set_temp("owner_name", "王三");
        ::setup();
}
