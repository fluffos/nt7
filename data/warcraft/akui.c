// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("奎奎[2;37;0m[2;37;0m", ({"kuikui"}));        
        set("gender", "男性");                
        set("long", "奎奎[2;37;0m
它是阿奎的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "akui");
        set("owner_name", "阿奎");
        set_temp("owner", "akui");
        set_temp("owner_name", "阿奎");
        ::setup();
}
