// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("农夫山泉[2;37;0m[2;37;0m", ({"nongfu"}));        
        set("gender", "男性");                
        set("long", "农夫山泉[2;37;0m
它是逍玄的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xiaoxuan");
        set("owner_name", "逍玄");
        set_temp("owner", "xiaoxuan");
        set_temp("owner_name", "逍玄");
        ::setup();
}
