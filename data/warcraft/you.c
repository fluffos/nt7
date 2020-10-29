// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
         set_name("日月镜", ({"lcnely"}));        
        set("gender", "男性");                
        set("long", "这就是一个猪头[2;37;0m
它是游讯的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "you");
        set("owner_name", "游讯");
        set_temp("owner", "you");
        set_temp("owner_name", "游讯");
        ::setup();
}
