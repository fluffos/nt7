// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小怪兽[2;37;0m[2;37;0m", ({"lauzhbb"}));        
        set("gender", "男性");                
        set("long", "小怪兽[2;37;0m
它是不辣奥特的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "lauzh");
        set("owner_name", "不辣奥特");
        set_temp("owner", "lauzh");
        set_temp("owner_name", "不辣奥特");
        ::setup();
}
