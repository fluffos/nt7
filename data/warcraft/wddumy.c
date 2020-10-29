// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("女秘[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "一位性感的女秘。[2;37;0m
它是张三狂的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "wddumy");
        set("owner_name", "张三狂");
        set_temp("owner", "wddumy");
        set_temp("owner_name", "张三狂");
        ::setup();
}
