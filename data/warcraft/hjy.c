// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("玄武[2;37;0m[2;37;0m", ({"xuanwu"}));        
        set("gender", "男性");                
        set("long", "玄武又叫玄冥，故又称北冥。[2;37;0m
它是张无忌的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "hjy");
        set("owner_name", "张无忌");
        set_temp("owner", "hjy");
        set_temp("owner_name", "张无忌");
        ::setup();
}
