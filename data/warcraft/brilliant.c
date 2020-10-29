// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m魑[1;33m魅[1;35m魍[1;32m魉[2;37;0m[2;37;0m[2;37;0m", ({"devil"}));        
        set("gender", "男性");                
        set("long", "魑魅魍魉[2;37;0m
它是天邪的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "brilliant");
        set("owner_name", "天邪");
        set_temp("owner", "brilliant");
        set_temp("owner_name", "天邪");
        ::setup();
}
