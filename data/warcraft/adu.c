// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m大王八[2;37;0m[2;37;0m", ({"wugui"}));        
        set("gender", "女性");                
        set("long", "超大的一直乌龟。[2;37;0m
它是阿毒的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "adu");
        set("owner_name", "阿毒");
        set_temp("owner", "adu");
        set_temp("owner_name", "阿毒");
        ::setup();
}
