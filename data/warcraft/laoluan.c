// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m白蛇[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "男性");                
        set("long", "话说这个是白娘子.....天天骑，天天骑。色艺！[2;37;0m
它是吾哈老乱的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "laoluan");
        set("owner_name", "吾哈老乱");
        set_temp("owner", "laoluan");
        set_temp("owner_name", "吾哈老乱");
        ::setup();
}
