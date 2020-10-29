// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("独孤疯猪[2;37;0m[2;37;0m", ({"lichasm"}));        
        set("gender", "男性");                
        set("long", "独孤疯猪[2;37;0m
它是师傅来了的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "lichd");
        set("owner_name", "师傅来了");
        set_temp("owner", "lichd");
        set_temp("owner_name", "师傅来了");
        ::setup();
}
