// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小鸡[2;37;0m[2;37;0m", ({"xji"}));        
        set("gender", "女性");                
        set("long", "小鸡[2;37;0m
它是小葵的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "kui");
        set("owner_name", "小葵");
        set_temp("owner", "kui");
        set_temp("owner_name", "小葵");
        ::setup();
}
