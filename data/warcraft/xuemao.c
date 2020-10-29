// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("雪花[2;37;0m[2;37;0m", ({"xuehua"}));        
        set("gender", "女性");                
        set("long", "白茫茫一片[2;37;0m
它是石雪梅的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xuemao");
        set("owner_name", "石雪梅");
        set_temp("owner", "xuemao");
        set_temp("owner_name", "石雪梅");
        ::setup();
}
