// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[30m小包包[2;37;0m[2;37;0m", ({"qianbaoc"}));        
        set("gender", "女性");                
        set("long", "$BLK$小包包[2;37;0m
它是钱很多的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "anc");
        set("owner_name", "钱很多");
        set_temp("owner", "anc");
        set_temp("owner_name", "钱很多");
        ::setup();
}
