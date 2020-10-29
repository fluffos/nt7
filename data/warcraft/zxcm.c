// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m凯钱[2;37;0m[2;37;0m", ({"zxcmpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是钱凯的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zxcm");
        set("owner_name", "钱凯");
        set_temp("owner", "zxcm");
        set_temp("owner_name", "钱凯");
        ::setup();
}
