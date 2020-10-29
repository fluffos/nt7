// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m花花[2;37;0m[2;37;0m", ({"tata"}));        
        set("gender", "男性");                
        set("long", "花花[2;37;0m
它是浪花儿的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "langhua");
        set("owner_name", "浪花儿");
        set_temp("owner", "langhua");
        set_temp("owner_name", "浪花儿");
        ::setup();
}
