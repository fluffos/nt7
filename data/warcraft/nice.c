// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m日本鬼子[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "女性");                
        set("long", "一个日本鬼子[2;37;0m
它是脑障碍者的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "nice");
        set("owner_name", "脑障碍者");
        set_temp("owner", "nice");
        set_temp("owner_name", "脑障碍者");
        ::setup();
}
