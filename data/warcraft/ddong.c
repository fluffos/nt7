// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m白虎[2;37;0m[2;37;0m", ({"bhu"}));        
        set("gender", "女性");                
        set("long", "白虎[2;37;0m
它是董东的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "ddong");
        set("owner_name", "董东");
        set_temp("owner", "ddong");
        set_temp("owner_name", "董东");
        ::setup();
}
