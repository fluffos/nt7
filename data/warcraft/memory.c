// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m纸夜[2;37;0m[2;37;0m", ({"paper"}));        
        set("gender", "女性");                
        set("long", "一片薄如蚕丝的纸页[2;37;0m
它是回忆的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "memory");
        set("owner_name", "回忆");
        set_temp("owner", "memory");
        set_temp("owner_name", "回忆");
        ::setup();
}
