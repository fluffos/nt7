// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("摩托车[2;37;0m[2;37;0m", ({"moto"}));        
        set("gender", "女性");                
        set("long", "这是一辆摩托车[2;37;0m
它是本国领导的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "fayan");
        set("owner_name", "本国领导");
        set_temp("owner", "fayan");
        set_temp("owner_name", "本国领导");
        ::setup();
}
