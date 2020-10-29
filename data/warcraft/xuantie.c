// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m我是小白[2;37;0m[2;37;0m", ({"xiaobai"}));        
        set("gender", "女性");                
        set("long", "$HIW$我是小白[2;37;0m
它是一大群人的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "xuantie");
        set("owner_name", "一大群人");
        set_temp("owner", "xuantie");
        set_temp("owner_name", "一大群人");
        ::setup();
}
