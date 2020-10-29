// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m玖钱[2;37;0m[2;37;0m", ({"zxcipet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是钱玖的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zxci");
        set("owner_name", "钱玖");
        set_temp("owner", "zxci");
        set_temp("owner_name", "钱玖");
        ::setup();
}
