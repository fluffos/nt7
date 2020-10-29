// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m东方天六[2;37;0m[2;37;0m", ({"eastee"}));        
        set("gender", "女性");                
        set("long", "$HIW$东方天六[2;37;0m
它是东方五的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "easte");
        set("owner_name", "东方五");
        set_temp("owner", "easte");
        set_temp("owner_name", "东方五");
        ::setup();
}
