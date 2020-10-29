// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小玄武[2;37;0m[2;37;0m", ({"madkid"}));        
        set("gender", "男性");                
        set("long", "小玄武[2;37;0m
它是张无量的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "madkiller");
        set("owner_name", "张无量");
        set_temp("owner", "madkiller");
        set_temp("owner_name", "张无量");
        ::setup();
}
