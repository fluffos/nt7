// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("玄武兽[2;37;0m[2;37;0m", ({"xuanwushou"}));        
        set("gender", "女性");                
        set("long", "防御坐骑[2;37;0m
它是张波的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "zhangbo");
        set("owner_name", "张波");
        set_temp("owner", "zhangbo");
        set_temp("owner_name", "张波");
        ::setup();
}
