// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m[5m跟斗云[2;37;0m[2;37;0m", ({"yun"}));        
        set("gender", "男性");                
        set("long", "龟仙人给的[2;37;0m
它是孙悟饭的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "wufan");
        set("owner_name", "孙悟饭");
        set_temp("owner", "wufan");
        set_temp("owner_name", "孙悟饭");
        ::setup();
}
