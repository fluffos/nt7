// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大法的[2;37;0m[2;37;0m", ({"yiyayo"}));        
        set("gender", "女性");                
        set("long", "大法的[2;37;0m
它是兵器一的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "zba");
        set("owner_name", "兵器一");
        set_temp("owner", "zba");
        set_temp("owner_name", "兵器一");
        ::setup();
}
