// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m静蕾[2;37;0m[2;37;0m", ({"mimi"}));        
        set("gender", "女性");                
        set("long", "很好看，很牛叉[2;37;0m
它是百里雷霆的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ggffgg");
        set("owner_name", "百里雷霆");
        set_temp("owner", "ggffgg");
        set_temp("owner_name", "百里雷霆");
        ::setup();
}
