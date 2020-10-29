// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小虎[2;37;0m[2;37;0m", ({"xiaohu"}));        
        set("gender", "男性");                
        set("long", "这是一只雪白的小老虎。[2;37;0m
它是包子的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "baozi");
        set("owner_name", "包子");
        set_temp("owner", "baozi");
        set_temp("owner_name", "包子");
        ::setup();
}
