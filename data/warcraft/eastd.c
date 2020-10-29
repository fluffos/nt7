// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m东方天四[2;37;0m[2;37;0m", ({"eastdd"}));        
        set("gender", "女性");                
        set("long", "$HIR$东方天四[2;37;0m
它是东方四的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "eastd");
        set("owner_name", "东方四");
        set_temp("owner", "eastd");
        set_temp("owner_name", "东方四");
        ::setup();
}
