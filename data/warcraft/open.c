// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("下为[2;37;0m[2;37;0m", ({"axd"}));        
        set("gender", "女性");                
        set("long", "搜索[2;37;0m
它是黑是的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "open");
        set("owner_name", "黑是");
        set_temp("owner", "open");
        set_temp("owner_name", "黑是");
        ::setup();
}
