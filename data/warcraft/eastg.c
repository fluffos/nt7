// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m东方天七[2;37;0m[2;37;0m", ({"eastgg"}));        
        set("gender", "女性");                
        set("long", "$HIW$东方天七[2;37;0m
它是东方七的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "eastg");
        set("owner_name", "东方七");
        set_temp("owner", "eastg");
        set_temp("owner_name", "东方七");
        ::setup();
}
