// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("哈哈[2;37;0m[2;37;0m", ({"hadley"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是瑞雪的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "smack");
        set("owner_name", "瑞雪");
        set_temp("owner", "smack");
        set_temp("owner_name", "瑞雪");
        ::setup();
}
