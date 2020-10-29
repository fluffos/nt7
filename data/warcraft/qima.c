// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[30m世京[2;37;0m[2;37;0m", ({"qimago"}));        
        set("gender", "女性");                
        set("long", "$BLK$世京[2;37;0m
它是奇闷已的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "qima");
        set("owner_name", "奇闷已");
        set_temp("owner", "qima");
        set_temp("owner_name", "奇闷已");
        ::setup();
}
