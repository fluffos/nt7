// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("玄武[2;37;0m[2;37;0m", ({"xuanwu"}));        
        set("gender", "男性");                
        set("long", "玄武[2;37;0m
它是赵屏风的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "kft");
        set("owner_name", "赵屏风");
        set_temp("owner", "kft");
        set_temp("owner_name", "赵屏风");
        ::setup();
}
