// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m柒研[2;37;0m[2;37;0m", ({"kosyjgpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是研柒的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kosyjg");
        set("owner_name", "研柒");
        set_temp("owner", "kosyjg");
        set_temp("owner_name", "研柒");
        ::setup();
}
