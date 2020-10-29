// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m勾钱[2;37;0m[2;37;0m", ({"zxckpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是钱勾的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zxck");
        set("owner_name", "钱勾");
        set_temp("owner", "zxck");
        set_temp("owner_name", "钱勾");
        ::setup();
}
