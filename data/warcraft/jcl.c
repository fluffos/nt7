// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m雪麒麟[2;37;0m[2;37;0m[2;37;0m", ({"lao"}));        
        set("gender", "男性");                
        set("long", "一只雪麒麟[2;37;0m
它是小浪的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "jcl");
        set("owner_name", "小浪");
        set_temp("owner", "jcl");
        set_temp("owner_name", "小浪");
        ::setup();
}
