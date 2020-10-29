// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小鸡[2;37;0m[2;37;0m", ({"jinhu"}));        
        set("gender", "男性");                
        set("long", "小鸡[2;37;0m
它是蛋药的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "dancat");
        set("owner_name", "蛋药");
        set_temp("owner", "dancat");
        set_temp("owner_name", "蛋药");
        ::setup();
}
