// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[35m风[1;35m剑[1;37m苍[31m月[2;37;0m[2;37;0m", ({"joe"}));        
        set("gender", "女性");                
        set("long", "相逢何必成相识[2;37;0m
它是灭雪的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "benben");
        set("owner_name", "灭雪");
        set_temp("owner", "benben");
        set_temp("owner_name", "灭雪");
        ::setup();
}
