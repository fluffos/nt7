// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("玄武[2;37;0m[2;37;0m", ({"xuanwu"}));        
        set("gender", "男性");                
        set("long", "玄武[2;37;0m
它是山华的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "shsh");
        set("owner_name", "山华");
        set_temp("owner", "shsh");
        set_temp("owner_name", "山华");
        ::setup();
}
