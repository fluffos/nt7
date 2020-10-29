// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;34m青面兽[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "男性");                
        set("long", "kick[2;37;0m
它是杨志的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yzhi");
        set("owner_name", "杨志");
        set_temp("owner", "yzhi");
        set_temp("owner_name", "杨志");
        ::setup();
}
