// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("酒神[2;37;0m[2;37;0m", ({"tuulong"}));        
        set("gender", "女性");                
        set("long", "使用报告[2;37;0m
它是永无止境的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "tuu");
        set("owner_name", "永无止境");
        set_temp("owner", "tuu");
        set_temp("owner_name", "永无止境");
        ::setup();
}
