// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m白龙马[2;37;0m[2;37;0m", ({"fff"}));        
        set("gender", "女性");                
        set("long", "白龙马[2;37;0m
它是蛛儿的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "zhu");
        set("owner_name", "蛛儿");
        set_temp("owner", "zhu");
        set_temp("owner_name", "蛛儿");
        ::setup();
}
