// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[30m驴子他妈[2;37;0m[2;37;0m", ({"lvzib"}));        
        set("gender", "女性");                
        set("long", "驴子他妈[2;37;0m
它是冥月秃驴的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ywub");
        set("owner_name", "冥月秃驴");
        set_temp("owner", "ywub");
        set_temp("owner_name", "冥月秃驴");
        ::setup();
}
