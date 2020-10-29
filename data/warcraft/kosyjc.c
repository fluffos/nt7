// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m叁研[2;37;0m[2;37;0m", ({"kosyjcpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是研叁的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kosyjc");
        set("owner_name", "研叁");
        set_temp("owner", "kosyjc");
        set_temp("owner_name", "研叁");
        ::setup();
}
