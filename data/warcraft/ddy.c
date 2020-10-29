// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"ddyy"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是堂亿的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ddy");
        set("owner_name", "堂亿");
        set_temp("owner", "ddy");
        set_temp("owner_name", "堂亿");
        ::setup();
}
