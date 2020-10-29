// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m刘德华[2;37;0m[2;37;0m", ({"liudehua"}));        
        set("gender", "男性");                
        set("long", "香港演员[2;37;0m
它是罪无可恕的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "blkc");
        set("owner_name", "罪无可恕");
        set_temp("owner", "blkc");
        set_temp("owner_name", "罪无可恕");
        ::setup();
}
