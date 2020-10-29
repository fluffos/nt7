// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m菊瓣[2;37;0m[2;37;0m", ({"asshole"}));        
        set("gender", "男性");                
        set("long", "爽[2;37;0m
它是爽歪歪的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "shuang");
        set("owner_name", "爽歪歪");
        set_temp("owner", "shuang");
        set_temp("owner_name", "爽歪歪");
        ::setup();
}
