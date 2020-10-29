// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m拾钱[2;37;0m[2;37;0m", ({"zxcjpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是钱拾的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zxcj");
        set("owner_name", "钱拾");
        set_temp("owner", "zxcj");
        set_temp("owner_name", "钱拾");
        ::setup();
}
