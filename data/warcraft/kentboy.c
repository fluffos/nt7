// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("火鸡[2;37;0m[2;37;0m", ({"kent"}));        
        set("gender", "男性");                
        set("long", "一只鸟？鸟一只？[2;37;0m
它是藤藤菜的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "kentboy");
        set("owner_name", "藤藤菜");
        set_temp("owner", "kentboy");
        set_temp("owner_name", "藤藤菜");
        ::setup();
}
