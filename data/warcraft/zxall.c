// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("奔龟[2;37;0m[2;37;0m", ({"bengui"}));        
        set("gender", "女性");                
        set("long", "奔龟[2;37;0m
它是舞丹的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "zxall");
        set("owner_name", "舞丹");
        set_temp("owner", "zxall");
        set_temp("owner_name", "舞丹");
        ::setup();
}
