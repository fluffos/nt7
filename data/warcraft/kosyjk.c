// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m勾研[2;37;0m[2;37;0m", ({"kosyjkpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是研勾的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kosyjk");
        set("owner_name", "研勾");
        set_temp("owner", "kosyjk");
        set_temp("owner_name", "研勾");
        ::setup();
}
