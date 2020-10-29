// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("图图[2;37;0m[2;37;0m", ({"ttz"}));        
        set("gender", "女性");                
        set("long", "傻不啦叽的土鳖。[2;37;0m
它是猪哥本本的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "justbbz");
        set("owner_name", "猪哥本本");
        set_temp("owner", "justbbz");
        set_temp("owner_name", "猪哥本本");
        ::setup();
}
