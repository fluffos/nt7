// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("草泥马[2;37;0m[2;37;0m", ({"cnm"}));        
        set("gender", "男性");                
        set("long", "神兽[2;37;0m
它是包包百的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "coca");
        set("owner_name", "包包百");
        set_temp("owner", "coca");
        set_temp("owner_name", "包包百");
        ::setup();
}
