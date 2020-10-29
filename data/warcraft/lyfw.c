// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m飞猪[2;37;0m[2;37;0m", ({"wdcat"}));        
        set("gender", "女性");                
        set("long", "猪在天上飞[2;37;0m
它是樱飞雪的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "lyfw");
        set("owner_name", "樱飞雪");
        set_temp("owner", "lyfw");
        set_temp("owner_name", "樱飞雪");
        ::setup();
}
