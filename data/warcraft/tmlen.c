// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m白虎[2;37;0m[2;37;0m[2;37;0m", ({"baihu"}));        
        set("gender", "女性");                
        set("long", "白虎[2;37;0m
它是月明中的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "tmlen");
        set("owner_name", "月明中");
        set_temp("owner", "tmlen");
        set_temp("owner_name", "月明中");
        ::setup();
}
