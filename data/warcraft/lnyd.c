// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("四哥麒麟[2;37;0m[2;37;0m", ({"lnydride"}));        
        set("gender", "男性");                
        set("long", "四哥麒麟[2;37;0m
它是龙里四哥的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lnyd");
        set("owner_name", "龙里四哥");
        set_temp("owner", "lnyd");
        set_temp("owner_name", "龙里四哥");
        ::setup();
}
