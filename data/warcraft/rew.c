// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("蒙古马[2;37;0m[2;37;0m", ({"rgg"}));        
        set("gender", "男性");                
        set("long", "一只鸟[2;37;0m
它是不丢不顶的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "rew");
        set("owner_name", "不丢不顶");
        set_temp("owner", "rew");
        set_temp("owner_name", "不丢不顶");
        ::setup();
}
