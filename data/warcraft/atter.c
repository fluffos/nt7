// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m古利亚诺斯[2;37;0m[2;37;0m", ({"lionheart"}));        
        set("gender", "男性");                
        set("long", "拥有散发著翠绿色光芒，名为古利亚诺斯[2;37;0m
它是薇塔的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "atter");
        set("owner_name", "薇塔");
        set_temp("owner", "atter");
        set_temp("owner_name", "薇塔");
        ::setup();
}
