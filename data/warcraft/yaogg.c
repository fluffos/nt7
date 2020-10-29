// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("嘎嘎嘎[2;37;0m[2;37;0m", ({"yaoggg"}));        
        set("gender", "男性");                
        set("long", "嘎嘎嘎[2;37;0m
它是药格格的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yaogg");
        set("owner_name", "药格格");
        set_temp("owner", "yaogg");
        set_temp("owner_name", "药格格");
        ::setup();
}
