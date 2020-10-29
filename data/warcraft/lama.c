// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[33m万年海龟[2;37;0m[2;37;0m", ({"wugui"}));        
        set("gender", "男性");                
        set("long", "打不死的万年英雄海龟，适合用来实验武功或暴力发泄！[2;37;0m
它是师太别走的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "lama");
        set("owner_name", "师太别走");
        set_temp("owner", "lama");
        set_temp("owner_name", "师太别走");
        ::setup();
}
