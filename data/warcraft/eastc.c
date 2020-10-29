// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m东方天三[2;37;0m[2;37;0m", ({"eastcc"}));        
        set("gender", "女性");                
        set("long", "$HIR$东方天三[2;37;0m
它是东方三的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "eastc");
        set("owner_name", "东方三");
        set_temp("owner", "eastc");
        set_temp("owner_name", "东方三");
        ::setup();
}
