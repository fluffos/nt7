// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m肆华[2;37;0m[2;37;0m", ({"mattpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是华肆的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "matt");
        set("owner_name", "华肆");
        set_temp("owner", "matt");
        set_temp("owner_name", "华肆");
        ::setup();
}
