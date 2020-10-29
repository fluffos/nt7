// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[30m小钱包[2;37;0m[2;37;0m", ({"qianbaoa"}));        
        set("gender", "男性");                
        set("long", "$BLK$小钱包[2;37;0m
它是钱多多的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ana");
        set("owner_name", "钱多多");
        set_temp("owner", "ana");
        set_temp("owner_name", "钱多多");
        ::setup();
}
