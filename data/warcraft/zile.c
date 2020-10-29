// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m好喵[2;37;0m[2;37;0m", ({"lilly"}));        
        set("gender", "女性");                
        set("long", "好坑好坑的大喵啊～～～[2;37;0m
它是蓝风轻的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "zile");
        set("owner_name", "蓝风轻");
        set_temp("owner", "zile");
        set_temp("owner_name", "蓝风轻");
        ::setup();
}
