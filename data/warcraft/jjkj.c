// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("蛇年[2;37;0m[2;37;0m", ({"jjyy"}));        
        set("gender", "男性");                
        set("long", "天下英豪出我辈，江湖一入催人老[2;37;0m
它是极品卡的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "jjkj");
        set("owner_name", "极品卡");
        set_temp("owner", "jjkj");
        set_temp("owner_name", "极品卡");
        ::setup();
}
