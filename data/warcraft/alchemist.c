// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m玉氵青[2;37;0m[2;37;0m", ({"yuqing"}));        
        set("gender", "男性");                
        set("long", "啊哈[2;37;0m
它是炼金术士的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "alchemist");
        set("owner_name", "炼金术士");
        set_temp("owner", "alchemist");
        set_temp("owner_name", "炼金术士");
        ::setup();
}
