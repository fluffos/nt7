// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m老乌龟[2;37;0m[2;37;0m", ({"wokao"}));        
        set("gender", "女性");                
        set("long", "不堪一击的老乌龟[2;37;0m
它是桃美闰的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "luss");
        set("owner_name", "桃美闰");
        set_temp("owner", "luss");
        set_temp("owner_name", "桃美闰");
        ::setup();
}
