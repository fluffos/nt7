// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m肆研[2;37;0m[2;37;0m", ({"kosyjdpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是研肆的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kosyjd");
        set("owner_name", "研肆");
        set_temp("owner", "kosyjd");
        set_temp("owner_name", "研肆");
        ::setup();
}
