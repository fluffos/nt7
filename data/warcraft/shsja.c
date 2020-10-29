// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("铁甲乌龟壳[2;37;0m[2;37;0m", ({"wugui"}));        
        set("gender", "男性");                
        set("long", "铁甲乌龟壳[2;37;0m
它是欧阳钝的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "shsja");
        set("owner_name", "欧阳钝");
        set_temp("owner", "shsja");
        set_temp("owner_name", "欧阳钝");
        ::setup();
}
