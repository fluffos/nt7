// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m陆钱[2;37;0m[2;37;0m", ({"zxcfpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是钱陆的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zxcf");
        set("owner_name", "钱陆");
        set_temp("owner", "zxcf");
        set_temp("owner_name", "钱陆");
        ::setup();
}
