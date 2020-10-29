// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小龙女[2;37;0m[2;37;0m", ({"laugmbb"}));        
        set("gender", "男性");                
        set("long", "小龙女[2;37;0m
它是不用右手的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "laugm");
        set("owner_name", "不用右手");
        set_temp("owner", "laugm");
        set_temp("owner_name", "不用右手");
        ::setup();
}
