// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[30m大包包[2;37;0m[2;37;0m", ({"qianbaod"}));        
        set("gender", "女性");                
        set("long", "$BLK$大包包[2;37;0m
它是钱很少的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "and");
        set("owner_name", "钱很少");
        set_temp("owner", "and");
        set_temp("owner_name", "钱很少");
        ::setup();
}
