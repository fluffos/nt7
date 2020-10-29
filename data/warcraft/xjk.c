// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m汗血宝马[2;37;0m[2;37;0m", ({"baby"}));        
        set("gender", "女性");                
        set("long", "魔幻神兽[2;37;0m
它是沐雪吻梅的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xjk");
        set("owner_name", "沐雪吻梅");
        set_temp("owner", "xjk");
        set_temp("owner_name", "沐雪吻梅");
        ::setup();
}
