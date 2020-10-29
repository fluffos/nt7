// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[37m波斯猫[2;37;0m[2;37;0m", ({"snowcat"}));        
        set("gender", "男性");                
        set("long", "一只温顺的波斯猫，正在懒懒的嗮太阳.[2;37;0m
它是飞雪的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "snow");
        set("owner_name", "飞雪");
        set_temp("owner", "snow");
        set_temp("owner_name", "飞雪");
        ::setup();
}
