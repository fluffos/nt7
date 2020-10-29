// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m强东版[5m[1;31m皮娃娃[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "男性");                
        set("long", "mygift[2;37;0m
它是潘金莲的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "pan");
        set("owner_name", "潘金莲");
        set_temp("owner", "pan");
        set_temp("owner_name", "潘金莲");
        ::setup();
}
