// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m白霜[2;37;0m[2;37;0m", ({"xiaobai"}));        
        set("gender", "男性");                
        set("long", "一条小白蛇[2;37;0m
它是五月的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ffox");
        set("owner_name", "五月");
        set_temp("owner", "ffox");
        set_temp("owner_name", "五月");
        ::setup();
}
