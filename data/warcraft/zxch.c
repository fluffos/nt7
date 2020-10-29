// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m捌钱[2;37;0m[2;37;0m", ({"zxchpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是钱捌的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zxch");
        set("owner_name", "钱捌");
        set_temp("owner", "zxch");
        set_temp("owner_name", "钱捌");
        ::setup();
}
