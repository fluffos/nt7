// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m红玉[2;37;0m[2;37;0m", ({"lianghys"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是梁红玉的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lianghy");
        set("owner_name", "梁红玉");
        set_temp("owner", "lianghy");
        set_temp("owner_name", "梁红玉");
        ::setup();
}
