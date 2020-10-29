// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[30m大钱包[2;37;0m[2;37;0m", ({"qianbaob"}));        
        set("gender", "男性");                
        set("long", "$BLK$大钱包[2;37;0m
它是钱少少的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "anb");
        set("owner_name", "钱少少");
        set_temp("owner", "anb");
        set_temp("owner_name", "钱少少");
        ::setup();
}
