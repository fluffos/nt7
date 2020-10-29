// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m千蛛万毒兽[2;37;0m[2;37;0m", ({"wds"}));        
        set("gender", "男性");                
        set("long", "看什么看，毒死你！！[2;37;0m
它是蓝百草的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "bdgz");
        set("owner_name", "蓝百草");
        set_temp("owner", "bdgz");
        set_temp("owner_name", "蓝百草");
        ::setup();
}
