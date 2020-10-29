// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小鸡仔[2;37;0m[2;37;0m", ({"chick"}));        
        set("gender", "女性");                
        set("long", "就是一直刚从蛋壳孵化出来的小鸡[2;37;0m
它是小曼的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "hanhan");
        set("owner_name", "小曼");
        set_temp("owner", "hanhan");
        set_temp("owner_name", "小曼");
        ::setup();
}
