// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("成[1;33m濑[1;35m心[1;34m美[1;37m[2;37;0m[2;37;0m", ({"togo"}));        
        set("gender", "女性");                
        set("long", "心美[2;37;0m
它是太虚子的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "taixuzi");
        set("owner_name", "太虚子");
        set_temp("owner", "taixuzi");
        set_temp("owner_name", "太虚子");
        ::setup();
}
