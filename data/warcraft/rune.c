// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m库符[2;37;0m[2;37;0m", ({"runepet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是符库的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "rune");
        set("owner_name", "符库");
        set_temp("owner", "rune");
        set_temp("owner_name", "符库");
        ::setup();
}
