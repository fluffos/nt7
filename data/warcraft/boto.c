// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("摸金令[2;37;0m[2;37;0m", ({"geng"}));        
        set("gender", "男性");                
        set("long", "这是一个穿山甲爪子所制的护身符，据说能护佑盗墓者...。[2;37;0m
它是胡八一的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "boto");
        set("owner_name", "胡八一");
        set_temp("owner", "boto");
        set_temp("owner_name", "胡八一");
        ::setup();
}
