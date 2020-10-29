// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m火[1;35m麒[1;33m麟[2;37;0m[2;37;0m", ({"qiqi"}));        
        set("gender", "男性");                
        set("long", "你按照狂风的指点开始飞快的念道[2;37;0m
它是无情枫的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xiaocc");
        set("owner_name", "无情枫");
        set_temp("owner", "xiaocc");
        set_temp("owner_name", "无情枫");
        ::setup();
}
