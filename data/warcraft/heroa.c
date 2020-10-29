// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m世京[2;37;0m[2;37;0m", ({"heroago"}));        
        set("gender", "男性");                
        set("long", "$HIW$世京[2;37;0m
它是风零一的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "heroa");
        set("owner_name", "风零一");
        set_temp("owner", "heroa");
        set_temp("owner_name", "风零一");
        ::setup();
}
