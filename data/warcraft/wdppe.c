// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("爱的[2;37;0m[2;37;0m", ({"mygift"}));        
        set("gender", "女性");                
        set("long", "爱的[2;37;0m
它是武当师五的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wdppe");
        set("owner_name", "武当师五");
        set_temp("owner", "wdppe");
        set_temp("owner_name", "武当师五");
        ::setup();
}
