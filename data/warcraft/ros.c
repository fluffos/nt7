// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m方世玉[2;37;0m[2;37;0m", ({"net"}));        
        set("gender", "女性");                
        set("long", "先用铁醋药水，次用竹板柴枝铁条层层换扎，筋络骨节血肉[2;37;0m
它是活性氧簇的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "ros");
        set("owner_name", "活性氧簇");
        set_temp("owner", "ros");
        set_temp("owner_name", "活性氧簇");
        ::setup();
}
