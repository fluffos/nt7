// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("虎牙[2;37;0m[2;37;0m", ({"ronger"}));        
        set("gender", "男性");                
        set("long", "这是头萌呆的小麒麟[2;37;0m
它是天若情的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ansonc");
        set("owner_name", "天若情");
        set_temp("owner", "ansonc");
        set_temp("owner_name", "天若情");
        ::setup();
}
