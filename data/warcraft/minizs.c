// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m玄武大帝[2;37;0m[2;37;0m", ({"minizsshou"}));        
        set("gender", "男性");                
        set("long", "四大神兽[2;37;0m
它是绝色的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "minizs");
        set("owner_name", "绝色");
        set_temp("owner", "minizs");
        set_temp("owner_name", "绝色");
        ::setup();
}
