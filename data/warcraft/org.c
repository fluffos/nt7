// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("你号[2;37;0m[2;37;0m", ({"jkl"}));        
        set("gender", "男性");                
        set("long", "asdf[2;37;0m
它是小柚子的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "org");
        set("owner_name", "小柚子");
        set_temp("owner", "org");
        set_temp("owner_name", "小柚子");
        ::setup();
}
