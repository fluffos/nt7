// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("百毒朱雀[2;37;0m[2;37;0m", ({"fgg"}));        
        set("gender", "男性");                
        set("long", "一只鸟[2;37;0m
它是玄魔子的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "fds");
        set("owner_name", "玄魔子");
        set_temp("owner", "fds");
        set_temp("owner_name", "玄魔子");
        ::setup();
}
