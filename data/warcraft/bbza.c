// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("本[2;37;0m[2;37;0m", ({"bba"}));        
        set("gender", "男性");                
        set("long", "xx[2;37;0m
它是本一的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "bbza");
        set("owner_name", "本一");
        set_temp("owner", "bbza");
        set_temp("owner_name", "本一");
        ::setup();
}
