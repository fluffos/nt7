// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("雪鸟[2;37;0m[2;37;0m", ({"xueoo"}));        
        set("gender", "女性");                
        set("long", "雪鸟[2;37;0m
它是蓝雪子的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wxue");
        set("owner_name", "蓝雪子");
        set_temp("owner", "wxue");
        set_temp("owner_name", "蓝雪子");
        ::setup();
}
