// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m照夜玉狮子[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "男性");                
        set("long", "这头照夜狮子通体上下，一色雪白，传说能日行千里，追风逐电。[2;37;0m
它是颜真卿的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "pen");
        set("owner_name", "颜真卿");
        set_temp("owner", "pen");
        set_temp("owner_name", "颜真卿");
        ::setup();
}
