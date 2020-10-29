// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m碧星麟[2;37;0m[2;37;0m", ({"greenstar"}));        
        set("gender", "男性");                
        set("long", "全身焕发着神秘青碧色的星点[2;37;0m
它是星魂的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xinger");
        set("owner_name", "星魂");
        set_temp("owner", "xinger");
        set_temp("owner_name", "星魂");
        ::setup();
}
