// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("游无穷[2;37;0m[2;37;0m", ({"tofly"}));        
        set("gender", "女性");                
        set("long", "飞[2;37;0m
它是谢风的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "togo");
        set("owner_name", "谢风");
        set_temp("owner", "togo");
        set_temp("owner_name", "谢风");
        ::setup();
}
