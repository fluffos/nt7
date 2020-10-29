// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;34m吉普[1;37m牧马人[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "男性");                
        set("long", "kick[2;37;0m
它是李连杰的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "starl");
        set("owner_name", "李连杰");
        set_temp("owner", "starl");
        set_temp("owner_name", "李连杰");
        ::setup();
}
