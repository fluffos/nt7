// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m白玉堂[2;37;0m[2;37;0m", ({"ins"}));        
        set("gender", "女性");                
        set("long", "这个是个老鼠精[2;37;0m
它是卡死的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "cos");
        set("owner_name", "卡死");
        set_temp("owner", "cos");
        set_temp("owner_name", "卡死");
        ::setup();
}
