// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("红色[2;37;0m[2;37;0m", ({"kaikai"}));        
        set("gender", "男性");                
        set("long", "王晓凯[2;37;0m
它是为谁疯狂的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "skillss");
        set("owner_name", "为谁疯狂");
        set_temp("owner", "skillss");
        set_temp("owner_name", "为谁疯狂");
        ::setup();
}
