// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("读书兽[2;37;0m[2;37;0m", ({"getbookride"}));        
        set("gender", "男性");                
        set("long", "读书兽[2;37;0m
它是拿书的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "getbook");
        set("owner_name", "拿书");
        set_temp("owner", "getbook");
        set_temp("owner_name", "拿书");
        ::setup();
}
