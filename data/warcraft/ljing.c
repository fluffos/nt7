// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m爆龙[2;37;0m[2;37;0m", ({"long"}));        
        set("gender", "男性");                
        set("long", "狂暴的龙[2;37;0m
它是山妹子的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ljing");
        set("owner_name", "山妹子");
        set_temp("owner", "ljing");
        set_temp("owner_name", "山妹子");
        ::setup();
}
