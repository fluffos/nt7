// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m人力三轮[2;37;0m[2;37;0m", ({"aoo"}));        
        set("gender", "女性");                
        set("long", "$HIW$人力三轮[2;37;0m
它是乡巴佬的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kooa");
        set("owner_name", "乡巴佬");
        set_temp("owner", "kooa");
        set_temp("owner_name", "乡巴佬");
        ::setup();
}
